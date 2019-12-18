#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum nl80211_auth_type { ____Placeholder_nl80211_auth_type } nl80211_auth_type ;

/* Variables and functions */
#define  NL80211_AUTHTYPE_AUTOMATIC 133 
#define  NL80211_AUTHTYPE_FT 132 
#define  NL80211_AUTHTYPE_NETWORK_EAP 131 
#define  NL80211_AUTHTYPE_OPEN_SYSTEM 130 
#define  NL80211_AUTHTYPE_SAE 129 
#define  NL80211_AUTHTYPE_SHARED_KEY 128 

__attribute__((used)) static const char *
wil_get_auth_type_name(enum nl80211_auth_type auth_type)
{
	switch (auth_type) {
	case NL80211_AUTHTYPE_OPEN_SYSTEM:
		return "OPEN_SYSTEM";
	case NL80211_AUTHTYPE_SHARED_KEY:
		return "SHARED_KEY";
	case NL80211_AUTHTYPE_FT:
		return "FT";
	case NL80211_AUTHTYPE_NETWORK_EAP:
		return "NETWORK_EAP";
	case NL80211_AUTHTYPE_SAE:
		return "SAE";
	case NL80211_AUTHTYPE_AUTOMATIC:
		return "AUTOMATIC";
	default:
		return "unknown";
	}
}