#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int inform_fw_driverctrldm; long undec_sm_pwdb; int /*<<< orphan*/  useramask; } ;
struct rate_adaptive {int pre_ratr_state; int ratr_state; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ dm; struct rate_adaptive ra; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; int /*<<< orphan*/  bssid; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update_rate_tbl ) (struct ieee80211_hw*,struct ieee80211_sta*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RATE ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DM_RATR_STA_HIGH 131 
#define  DM_RATR_STA_LOW 130 
#define  DM_RATR_STA_MIDDLE 129 
#define  DM_RATR_STA_ULTRALOW 128 
 int /*<<< orphan*/  FW_CMD_CTRL_DM_BY_DRIVER ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,long,int,int,int) ; 
 int hal_get_firmwareversion (struct rtl_priv*) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtl92s_phy_set_fw_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* rtl_find_sta (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct ieee80211_sta*,int,int) ; 

__attribute__((used)) static void _rtl92s_dm_refresh_rateadaptive_mask(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rate_adaptive *ra = &(rtlpriv->ra);
	struct ieee80211_sta *sta = NULL;
	u32 low_rssi_thresh = 0;
	u32 middle_rssi_thresh = 0;
	u32 high_rssi_thresh = 0;

	if (is_hal_stop(rtlhal))
		return;

	if (!rtlpriv->dm.useramask)
		return;

	if (hal_get_firmwareversion(rtlpriv) >= 61 &&
	    !rtlpriv->dm.inform_fw_driverctrldm) {
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_CTRL_DM_BY_DRIVER);
		rtlpriv->dm.inform_fw_driverctrldm = true;
	}

	if ((mac->link_state == MAC80211_LINKED) &&
	    (mac->opmode == NL80211_IFTYPE_STATION)) {
		switch (ra->pre_ratr_state) {
		case DM_RATR_STA_HIGH:
			high_rssi_thresh = 40;
			middle_rssi_thresh = 30;
			low_rssi_thresh = 20;
			break;
		case DM_RATR_STA_MIDDLE:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 30;
			low_rssi_thresh = 20;
			break;
		case DM_RATR_STA_LOW:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 34;
			low_rssi_thresh = 20;
			break;
		case DM_RATR_STA_ULTRALOW:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 34;
			low_rssi_thresh = 24;
			break;
		default:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 34;
			low_rssi_thresh = 24;
			break;
		}

		if (rtlpriv->dm.undec_sm_pwdb > (long)high_rssi_thresh) {
			ra->ratr_state = DM_RATR_STA_HIGH;
		} else if (rtlpriv->dm.undec_sm_pwdb >
			   (long)middle_rssi_thresh) {
			ra->ratr_state = DM_RATR_STA_LOW;
		} else if (rtlpriv->dm.undec_sm_pwdb >
			   (long)low_rssi_thresh) {
			ra->ratr_state = DM_RATR_STA_LOW;
		} else {
			ra->ratr_state = DM_RATR_STA_ULTRALOW;
		}

		if (ra->pre_ratr_state != ra->ratr_state) {
			RT_TRACE(rtlpriv, COMP_RATE, DBG_LOUD,
				 "RSSI = %ld RSSI_LEVEL = %d PreState = %d, CurState = %d\n",
				 rtlpriv->dm.undec_sm_pwdb, ra->ratr_state,
				 ra->pre_ratr_state, ra->ratr_state);

			rcu_read_lock();
			sta = rtl_find_sta(hw, mac->bssid);
			if (sta)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta,
							   ra->ratr_state,
							   true);
			rcu_read_unlock();

			ra->pre_ratr_state = ra->ratr_state;
		}
	}
}