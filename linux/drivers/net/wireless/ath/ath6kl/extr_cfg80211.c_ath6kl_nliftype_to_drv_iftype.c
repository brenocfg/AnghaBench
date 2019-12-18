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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  ADHOC_NETWORK ; 
 int /*<<< orphan*/  AP_NETWORK ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  INFRA_NETWORK ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 

__attribute__((used)) static int ath6kl_nliftype_to_drv_iftype(enum nl80211_iftype type, u8 *nw_type)
{
	switch (type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		*nw_type = INFRA_NETWORK;
		break;
	case NL80211_IFTYPE_ADHOC:
		*nw_type = ADHOC_NETWORK;
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
		*nw_type = AP_NETWORK;
		break;
	default:
		ath6kl_err("invalid interface type %u\n", type);
		return -ENOTSUPP;
	}

	return 0;
}