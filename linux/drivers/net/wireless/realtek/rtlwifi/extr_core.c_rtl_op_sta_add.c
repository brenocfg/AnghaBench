#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rtl_sta_info {int /*<<< orphan*/  mac_addr; void* wireless_mode; int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/  entry_list_lock; } ;
struct rtl_priv {TYPE_5__* cfg; TYPE_1__ locks; int /*<<< orphan*/  entry_list; } ;
struct rtl_mac {scalar_t__ p2p; } ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_8__ {scalar_t__ vht_supported; } ;
struct TYPE_7__ {scalar_t__ ht_supported; } ;
struct ieee80211_sta {int* supp_rates; int /*<<< orphan*/  addr; TYPE_3__ vht_cap; TYPE_2__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_10__ {TYPE_4__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* update_rate_tbl ) (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* WIRELESS_MODE_A ; 
 void* WIRELESS_MODE_AC_5G ; 
 void* WIRELESS_MODE_B ; 
 void* WIRELESS_MODE_G ; 
 void* WIRELESS_MODE_N_24G ; 
 void* WIRELESS_MODE_N_5G ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl_op_sta_add(struct ieee80211_hw *hw,
			 struct ieee80211_vif *vif,
			 struct ieee80211_sta *sta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_sta_info *sta_entry;

	if (sta) {
		sta_entry = (struct rtl_sta_info *)sta->drv_priv;
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_add_tail(&sta_entry->list, &rtlpriv->entry_list);
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);
		if (rtlhal->current_bandtype == BAND_ON_2_4G) {
			sta_entry->wireless_mode = WIRELESS_MODE_G;
			if (sta->supp_rates[0] <= 0xf)
				sta_entry->wireless_mode = WIRELESS_MODE_B;
			if (sta->ht_cap.ht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_N_24G;

			if (vif->type == NL80211_IFTYPE_ADHOC)
				sta_entry->wireless_mode = WIRELESS_MODE_G;
		} else if (rtlhal->current_bandtype == BAND_ON_5G) {
			sta_entry->wireless_mode = WIRELESS_MODE_A;
			if (sta->ht_cap.ht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_N_5G;
			if (sta->vht_cap.vht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_AC_5G;

			if (vif->type == NL80211_IFTYPE_ADHOC)
				sta_entry->wireless_mode = WIRELESS_MODE_A;
		}
		/*disable cck rate for p2p*/
		if (mac->p2p)
			sta->supp_rates[0] &= 0xfffffff0;

		memcpy(sta_entry->mac_addr, sta->addr, ETH_ALEN);
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
			"Add sta addr is %pM\n", sta->addr);
		rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0, true);
	}

	return 0;
}