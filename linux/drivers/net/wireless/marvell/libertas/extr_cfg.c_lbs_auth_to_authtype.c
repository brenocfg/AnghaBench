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
 int ENOTSUPP ; 
#define  NL80211_AUTHTYPE_AUTOMATIC 131 
#define  NL80211_AUTHTYPE_NETWORK_EAP 130 
#define  NL80211_AUTHTYPE_OPEN_SYSTEM 129 
#define  NL80211_AUTHTYPE_SHARED_KEY 128 

__attribute__((used)) static int lbs_auth_to_authtype(enum nl80211_auth_type auth_type)
{
	int ret = -ENOTSUPP;

	switch (auth_type) {
	case NL80211_AUTHTYPE_OPEN_SYSTEM:
	case NL80211_AUTHTYPE_SHARED_KEY:
		ret = auth_type;
		break;
	case NL80211_AUTHTYPE_AUTOMATIC:
		ret = NL80211_AUTHTYPE_OPEN_SYSTEM;
		break;
	case NL80211_AUTHTYPE_NETWORK_EAP:
		ret = 0x80;
		break;
	default:
		/* silence compiler */
		break;
	}
	return ret;
}