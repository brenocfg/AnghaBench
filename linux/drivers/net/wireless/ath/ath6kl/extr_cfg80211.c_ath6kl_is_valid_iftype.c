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
typedef  int u8 ;
struct ath6kl {int vif_max; int avail_idx_map; int max_norm_iface; scalar_t__ num_vif; scalar_t__ ibss_if_active; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int BIT (int) ; 
 int NL80211_IFTYPE_ADHOC ; 
 int NL80211_IFTYPE_AP ; 
 int NL80211_IFTYPE_P2P_CLIENT ; 
 int NL80211_IFTYPE_P2P_GO ; 
 int NL80211_IFTYPE_STATION ; 
 scalar_t__ ath6kl_nliftype_to_drv_iftype (int,int*) ; 

__attribute__((used)) static bool ath6kl_is_valid_iftype(struct ath6kl *ar, enum nl80211_iftype type,
				   u8 *if_idx, u8 *nw_type)
{
	int i;

	if (ath6kl_nliftype_to_drv_iftype(type, nw_type))
		return false;

	if (ar->ibss_if_active || ((type == NL80211_IFTYPE_ADHOC) &&
				   ar->num_vif))
		return false;

	if (type == NL80211_IFTYPE_STATION ||
	    type == NL80211_IFTYPE_AP || type == NL80211_IFTYPE_ADHOC) {
		for (i = 0; i < ar->vif_max; i++) {
			if ((ar->avail_idx_map) & BIT(i)) {
				*if_idx = i;
				return true;
			}
		}
	}

	if (type == NL80211_IFTYPE_P2P_CLIENT ||
	    type == NL80211_IFTYPE_P2P_GO) {
		for (i = ar->max_norm_iface; i < ar->vif_max; i++) {
			if ((ar->avail_idx_map) & BIT(i)) {
				*if_idx = i;
				return true;
			}
		}
	}

	return false;
}