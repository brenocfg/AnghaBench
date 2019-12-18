#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl_sta_info {void* wireless_mode; } ;
struct TYPE_10__ {scalar_t__ p2p_ps_mode; } ;
struct rtl_ps_ctl {int report_linked; TYPE_1__ p2p_ps_info; } ;
struct TYPE_18__ {int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_13__ {TYPE_3__* btc_ops; } ;
struct TYPE_11__ {scalar_t__ supp_phymode_switch; } ;
struct rtl_priv {TYPE_9__ locks; TYPE_8__* cfg; TYPE_4__ btcoexist; TYPE_2__ dm; } ;
struct rtl_mac {int beacon_enabled; scalar_t__ link_state; scalar_t__ current_ampdu_density; scalar_t__ current_ampdu_factor; int ht_enable; int vht_enable; int basic_rates; void* mode; scalar_t__ bssid; void* vendor; int /*<<< orphan*/  max_mss_density; int /*<<< orphan*/  slot_time; scalar_t__ short_preamble; int /*<<< orphan*/  use_cts_protect; int /*<<< orphan*/  assoc_id; scalar_t__ cnt_after_linked; int /*<<< orphan*/  beacon_interval; } ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {scalar_t__ vht_supported; } ;
struct TYPE_14__ {scalar_t__ ampdu_density; scalar_t__ ampdu_factor; scalar_t__ ht_supported; } ;
struct ieee80211_sta {int* supp_rates; TYPE_6__ vht_cap; TYPE_5__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_bss_conf {scalar_t__ bssid; scalar_t__ use_short_slot; scalar_t__ use_short_preamble; int /*<<< orphan*/  use_cts_prot; int /*<<< orphan*/  aid; scalar_t__ assoc; int /*<<< orphan*/  beacon_int; scalar_t__ enable_beacon; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_17__ {TYPE_7__* ops; int /*<<< orphan*/ * maps; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ (* get_btc_status ) () ;int /*<<< orphan*/  (* set_network_type ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* chk_switch_dmdp ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* update_rate_tbl ) (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* linked_set_reg ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* set_bcn_intv ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* update_interrupt_mask ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* btc_mediastatus_notify ) (struct rtl_priv*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_HT ; 
 int /*<<< orphan*/  COMP_BEACON ; 
 int /*<<< orphan*/  COMP_EASY_CONCURRENT ; 
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HW_VAR_ACK_PREAMBLE ; 
 int /*<<< orphan*/  HW_VAR_AMPDU_FACTOR ; 
 int /*<<< orphan*/  HW_VAR_AMPDU_MIN_SPACE ; 
 int /*<<< orphan*/  HW_VAR_BASIC_RATE ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_H2C_FW_JOINBSSRPT ; 
 int /*<<< orphan*/  HW_VAR_KEEP_ALIVE ; 
 int /*<<< orphan*/  HW_VAR_SHORTGI_DENSITY ; 
 int /*<<< orphan*/  HW_VAR_SLOT_TIME ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_ESS ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_OFF ; 
 int /*<<< orphan*/  IEEE80211_SMPS_STATIC ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MAC80211_NOLINK ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  P2P_PS_DISABLE ; 
 scalar_t__ P2P_PS_NONE ; 
 void* PEER_UNKNOWN ; 
 size_t RTL_IBSS_INT_MASKS ; 
 int /*<<< orphan*/  RTL_SLOT_TIME_20 ; 
 int /*<<< orphan*/  RTL_SLOT_TIME_9 ; 
 scalar_t__ RT_MEDIA_CONNECT ; 
 scalar_t__ RT_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* WIRELESS_MODE_A ; 
 void* WIRELESS_MODE_AC_24G ; 
 void* WIRELESS_MODE_AC_5G ; 
 void* WIRELESS_MODE_B ; 
 void* WIRELESS_MODE_G ; 
 void* WIRELESS_MODE_N_24G ; 
 void* WIRELESS_MODE_N_5G ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  cfg80211_unlink_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  eth_zero_addr (scalar_t__) ; 
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtl_cam_reset_all_entry (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_cam_reset_sec_info (struct ieee80211_hw*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_lps_leave (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_p2p_ps_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_send_smps_action (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_beacon_frame (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub11 () ; 
 int /*<<< orphan*/  stub12 (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stub13 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub14 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub15 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub16 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub17 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub18 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub19 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub8 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub9 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_op_bss_info_changed(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_bss_conf *bss_conf,
				    u32 changed)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.conf_mutex);
	if (vif->type == NL80211_IFTYPE_ADHOC ||
	    vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_MESH_POINT) {
		if (changed & BSS_CHANGED_BEACON ||
		    (changed & BSS_CHANGED_BEACON_ENABLED &&
		     bss_conf->enable_beacon)) {
			if (mac->beacon_enabled == 0) {
				RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
					 "BSS_CHANGED_BEACON_ENABLED\n");

				/*start hw beacon interrupt. */
				/*rtlpriv->cfg->ops->set_bcn_reg(hw); */
				mac->beacon_enabled = 1;
				rtlpriv->cfg->ops->update_interrupt_mask(hw,
						rtlpriv->cfg->maps
						[RTL_IBSS_INT_MASKS], 0);

				if (rtlpriv->cfg->ops->linked_set_reg)
					rtlpriv->cfg->ops->linked_set_reg(hw);
				send_beacon_frame(hw, vif);
			}
		}
		if ((changed & BSS_CHANGED_BEACON_ENABLED &&
		    !bss_conf->enable_beacon)) {
			if (mac->beacon_enabled == 1) {
				RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
					 "ADHOC DISABLE BEACON\n");

				mac->beacon_enabled = 0;
				rtlpriv->cfg->ops->update_interrupt_mask(hw, 0,
						rtlpriv->cfg->maps
						[RTL_IBSS_INT_MASKS]);
			}
		}
		if (changed & BSS_CHANGED_BEACON_INT) {
			RT_TRACE(rtlpriv, COMP_BEACON, DBG_TRACE,
				 "BSS_CHANGED_BEACON_INT\n");
			mac->beacon_interval = bss_conf->beacon_int;
			rtlpriv->cfg->ops->set_bcn_intv(hw);
		}
	}

	/*TODO: reference to enum ieee80211_bss_change */
	if (changed & BSS_CHANGED_ASSOC) {
		u8 mstatus;

		if (bss_conf->assoc) {
			struct ieee80211_sta *sta = NULL;
			u8 keep_alive = 10;

			mstatus = RT_MEDIA_CONNECT;
			/* we should reset all sec info & cam
			 * before set cam after linked, we should not
			 * reset in disassoc, that will cause tkip->wep
			 * fail because some flag will be wrong */
			/* reset sec info */
			rtl_cam_reset_sec_info(hw);
			/* reset cam to fix wep fail issue
			 * when change from wpa to wep */
			rtl_cam_reset_all_entry(hw);

			mac->link_state = MAC80211_LINKED;
			mac->cnt_after_linked = 0;
			mac->assoc_id = bss_conf->aid;
			memcpy(mac->bssid, bss_conf->bssid, ETH_ALEN);

			if (rtlpriv->cfg->ops->linked_set_reg)
				rtlpriv->cfg->ops->linked_set_reg(hw);

			rcu_read_lock();
			sta = ieee80211_find_sta(vif, (u8 *)bss_conf->bssid);
			if (!sta) {
				rcu_read_unlock();
				goto out;
			}
			RT_TRACE(rtlpriv, COMP_EASY_CONCURRENT, DBG_LOUD,
				 "send PS STATIC frame\n");
			if (rtlpriv->dm.supp_phymode_switch) {
				if (sta->ht_cap.ht_supported)
					rtl_send_smps_action(hw, sta,
							IEEE80211_SMPS_STATIC);
			}

			if (rtlhal->current_bandtype == BAND_ON_5G) {
				mac->mode = WIRELESS_MODE_A;
			} else {
				if (sta->supp_rates[0] <= 0xf)
					mac->mode = WIRELESS_MODE_B;
				else
					mac->mode = WIRELESS_MODE_G;
			}

			if (sta->ht_cap.ht_supported) {
				if (rtlhal->current_bandtype == BAND_ON_2_4G)
					mac->mode = WIRELESS_MODE_N_24G;
				else
					mac->mode = WIRELESS_MODE_N_5G;
			}

			if (sta->vht_cap.vht_supported) {
				if (rtlhal->current_bandtype == BAND_ON_5G)
					mac->mode = WIRELESS_MODE_AC_5G;
				else
					mac->mode = WIRELESS_MODE_AC_24G;
			}

			if (vif->type == NL80211_IFTYPE_STATION)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0,
								   true);
			rcu_read_unlock();

			/* to avoid AP Disassociation caused by inactivity */
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_KEEP_ALIVE,
						      (u8 *)(&keep_alive));

			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
				 "BSS_CHANGED_ASSOC\n");
		} else {
			struct cfg80211_bss *bss = NULL;

			mstatus = RT_MEDIA_DISCONNECT;

			if (mac->link_state == MAC80211_LINKED)
				rtl_lps_leave(hw);
			if (ppsc->p2p_ps_info.p2p_ps_mode > P2P_PS_NONE)
				rtl_p2p_ps_cmd(hw, P2P_PS_DISABLE);
			mac->link_state = MAC80211_NOLINK;

			bss = cfg80211_get_bss(hw->wiphy, NULL,
					       (u8 *)mac->bssid, NULL, 0,
					       IEEE80211_BSS_TYPE_ESS,
					       IEEE80211_PRIVACY_OFF);

			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
				 "bssid = %pMF\n", mac->bssid);

			if (bss) {
				cfg80211_unlink_bss(hw->wiphy, bss);
				cfg80211_put_bss(hw->wiphy, bss);
				RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
					 "cfg80211_unlink !!\n");
			}

			eth_zero_addr(mac->bssid);
			mac->vendor = PEER_UNKNOWN;
			mac->mode = 0;

			if (rtlpriv->dm.supp_phymode_switch) {
				if (rtlpriv->cfg->ops->chk_switch_dmdp)
					rtlpriv->cfg->ops->chk_switch_dmdp(hw);
			}
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
				 "BSS_CHANGED_UN_ASSOC\n");
		}
		rtlpriv->cfg->ops->set_network_type(hw, vif->type);
		/* For FW LPS:
		 * To tell firmware we have connected or disconnected
		 */
		rtlpriv->cfg->ops->set_hw_reg(hw,
					      HW_VAR_H2C_FW_JOINBSSRPT,
					      (u8 *)(&mstatus));
		ppsc->report_linked = (mstatus == RT_MEDIA_CONNECT) ?
				      true : false;

		if (rtlpriv->cfg->ops->get_btc_status())
			rtlpriv->btcoexist.btc_ops->btc_mediastatus_notify(
							rtlpriv, mstatus);
	}

	if (changed & BSS_CHANGED_ERP_CTS_PROT) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "BSS_CHANGED_ERP_CTS_PROT\n");
		mac->use_cts_protect = bss_conf->use_cts_prot;
	}

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
			 "BSS_CHANGED_ERP_PREAMBLE use short preamble:%x\n",
			  bss_conf->use_short_preamble);

		mac->short_preamble = bss_conf->use_short_preamble;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ACK_PREAMBLE,
					      (u8 *)(&mac->short_preamble));
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "BSS_CHANGED_ERP_SLOT\n");

		if (bss_conf->use_short_slot)
			mac->slot_time = RTL_SLOT_TIME_9;
		else
			mac->slot_time = RTL_SLOT_TIME_20;

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
					      (u8 *)(&mac->slot_time));
	}

	if (changed & BSS_CHANGED_HT) {
		struct ieee80211_sta *sta = NULL;

		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "BSS_CHANGED_HT\n");

		rcu_read_lock();
		sta = ieee80211_find_sta(vif, (u8 *)bss_conf->bssid);
		if (sta) {
			if (sta->ht_cap.ampdu_density >
			    mac->current_ampdu_density)
				mac->current_ampdu_density =
				    sta->ht_cap.ampdu_density;
			if (sta->ht_cap.ampdu_factor <
			    mac->current_ampdu_factor)
				mac->current_ampdu_factor =
				    sta->ht_cap.ampdu_factor;
		}
		rcu_read_unlock();

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SHORTGI_DENSITY,
					      (u8 *)(&mac->max_mss_density));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AMPDU_FACTOR,
					      &mac->current_ampdu_factor);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AMPDU_MIN_SPACE,
					      &mac->current_ampdu_density);
	}

	if (changed & BSS_CHANGED_BSSID) {
		u32 basic_rates;
		struct ieee80211_sta *sta = NULL;

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BSSID,
					      (u8 *)bss_conf->bssid);

		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
			 "bssid: %pM\n", bss_conf->bssid);

		mac->vendor = PEER_UNKNOWN;
		memcpy(mac->bssid, bss_conf->bssid, ETH_ALEN);

		rcu_read_lock();
		sta = ieee80211_find_sta(vif, (u8 *)bss_conf->bssid);
		if (!sta) {
			rcu_read_unlock();
			goto out;
		}

		if (rtlhal->current_bandtype == BAND_ON_5G) {
			mac->mode = WIRELESS_MODE_A;
		} else {
			if (sta->supp_rates[0] <= 0xf)
				mac->mode = WIRELESS_MODE_B;
			else
				mac->mode = WIRELESS_MODE_G;
		}

		if (sta->ht_cap.ht_supported) {
			if (rtlhal->current_bandtype == BAND_ON_2_4G)
				mac->mode = WIRELESS_MODE_N_24G;
			else
				mac->mode = WIRELESS_MODE_N_5G;
		}

		if (sta->vht_cap.vht_supported) {
			if (rtlhal->current_bandtype == BAND_ON_5G)
				mac->mode = WIRELESS_MODE_AC_5G;
			else
				mac->mode = WIRELESS_MODE_AC_24G;
		}

		/* just station need it, because ibss & ap mode will
		 * set in sta_add, and will be NULL here */
		if (vif->type == NL80211_IFTYPE_STATION) {
			struct rtl_sta_info *sta_entry;

			sta_entry = (struct rtl_sta_info *)sta->drv_priv;
			sta_entry->wireless_mode = mac->mode;
		}

		if (sta->ht_cap.ht_supported) {
			mac->ht_enable = true;

			/*
			 * for cisco 1252 bw20 it's wrong
			 * if (ht_cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) {
			 *	mac->bw_40 = true;
			 * }
			 * */
		}

		if (sta->vht_cap.vht_supported)
			mac->vht_enable = true;

		if (changed & BSS_CHANGED_BASIC_RATES) {
			/* for 5G must << RATE_6M_INDEX = 4,
			 * because 5G have no cck rate*/
			if (rtlhal->current_bandtype == BAND_ON_5G)
				basic_rates = sta->supp_rates[1] << 4;
			else
				basic_rates = sta->supp_rates[0];

			mac->basic_rates = basic_rates;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
					(u8 *)(&basic_rates));
		}
		rcu_read_unlock();
	}
out:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
}