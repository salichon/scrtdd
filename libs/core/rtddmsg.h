/***************************************************************************
 *   Copyright (C) by ETHZ/SED                                             *
 *                                                                         *
 *   You can redistribute and/or modify this program under the             *
 *   terms of the "SED Public License for Seiscomp Contributions"          *
 *                                                                         *
 *   You should have received a copy of the "SED Public License for        *
 *   Seiscomp Contributions" with this. If not, you can find it at         *
 *   http://www.seismo.ethz.ch/static/seiscomp_contrib/license.txt         *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   "SED Public License for Seiscomp Contributions" for more details      *
 *                                                                         *
 *   Developed by Luca Scarabello <luca.scarabello@sed.ethz.ch>            *
 ***************************************************************************/
 
#ifndef __RTDD_CORE_RTDDMSG_H__
#define __RTDD_CORE_RTDDMSG_H__

#include <seiscomp3/io/archive/xmlarchive.h>
#include <seiscomp3/communication/systemmessages.h>
#include <seiscomp3/core/genericmessage.h>
#include <seiscomp3/datamodel/origin.h>

namespace Seiscomp {

DEFINE_SMARTPOINTER(RTDDRelocateRequestMessage);

/**
 * \brief Message for requesting a clearing of the cache
 * This message type requests a response from a peer. 
 */
class SC_SYSTEM_CLIENT_API RTDDRelocateRequestMessage : public Seiscomp::Core::Message {
    DECLARE_SC_CLASS(RTDDRelocateRequestMessage);
    DECLARE_SERIALIZATION;

    public:
        //! Constructor
        RTDDRelocateRequestMessage() : _origin(0), _publicID("") { }

        void setOrigin(DataModel::Origin* org) { _origin = org; _publicID = ""; }
        DataModel::Origin* getOrigin() const { return _origin; }

        void setOriginId(const std::string& orgId) { _publicID = orgId; _origin = 0; }
        std::string getOriginId() const { return _publicID; }

        void setProfile(const std::string& name) { _profile = name; }
        std::string getProfile() const { return _profile; }

        //! Implemented interface from Message
        virtual bool empty() const  { return false; }

    private:
        DataModel::Origin* _origin; // either _origin or _publicID must be defined
        std::string _publicID;
        std::string _profile;
};

DEFINE_SMARTPOINTER(RTDDRelocateResponseMessage);

/**
 * \brief Message to respond to a clear cache request
 */
class SC_SYSTEM_CLIENT_API RTDDRelocateResponseMessage : public Seiscomp::Core::Message {
    DECLARE_SC_CLASS(RTDDRelocateResponseMessage);
    DECLARE_SERIALIZATION;

    public:
        //! Constructor
        RTDDRelocateResponseMessage() : _relocatedOrigin(0), _error("") {}

        void setOrigin(DataModel::Origin* org) { _relocatedOrigin = org; }
        DataModel::Origin* getOrigin() { return _relocatedOrigin; }

        void setError(const std::string err) { _error = err; }
        std::string getError() const { return _error; }
        bool hasError() const { return !_error.empty(); }

        //! Implemented interface from Message
        virtual bool empty() const  { return false; }

    private:
        DataModel::Origin* _relocatedOrigin;
        std::string _error;
};

} // namespace Seiscomp

#endif
