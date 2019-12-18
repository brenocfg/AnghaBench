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
typedef  int u32 ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int BIT (int) ; 
 int EXT_BSSID_1 ; 
 int EXT_BSSID_END ; 
 int HW_BSSID_0 ; 
 int HW_BSSID_1 ; 
 int HW_BSSID_MAX ; 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int get_omac_idx(enum nl80211_iftype type, u32 mask)
{
	int i;

	switch (type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
		/* ap use hw bssid 0 and ext bssid */
		if (~mask & BIT(HW_BSSID_0))
			return HW_BSSID_0;

		for (i = EXT_BSSID_1; i < EXT_BSSID_END; i++)
			if (~mask & BIT(i))
				return i;

		break;
	case NL80211_IFTYPE_STATION:
		/* sta use hw bssid other than 0 */
		for (i = HW_BSSID_1; i < HW_BSSID_MAX; i++)
			if (~mask & BIT(i))
				return i;

		break;
	default:
		WARN_ON(1);
		break;
	};

	return -1;
}