#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtl_ps_ctl {scalar_t__ rfpwr_state; } ;
struct rtl_phy {int iqk_initialized; void** rfreg_chnlval; int /*<<< orphan*/  rf_mode; } ;
struct rtl_priv {TYPE_2__* cfg; struct rtl_phy phy; } ;
struct rtl_mac {int /*<<< orphan*/  mac_addr; } ;
struct rtl_hal {int fw_ready; int /*<<< orphan*/  version; scalar_t__ last_hmeboxnum; int /*<<< orphan*/  hw_type; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  HARDWARE_TYPE_RTL8192CU ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 int /*<<< orphan*/  IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VENDOR_UMC_A_CUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RF_OP_BY_SW_3WIRE ; 
 int /*<<< orphan*/  RF_RX_G1 ; 
 int /*<<< orphan*/  RF_RX_G2 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _initpabias (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92cu_hw_configure (struct ieee80211_hw*) ; 
 int _rtl92cu_init_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92cu_phy_param_tab_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl92c_dm_check_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_init (struct ieee80211_hw*) ; 
 int rtl92c_download_fw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_iq_calibrate (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92c_phy_lc_calibrate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_rf_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_set_rfpath_switch (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92cu_bb_block_on (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92cu_enable_hw_security_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92cu_phy_bb_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92cu_phy_mac_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_cam_reset_all_entry (struct ieee80211_hw*) ; 
 void* rtl_get_rfreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtl92cu_hw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	int err = 0;
	unsigned long flags;

	/* As this function can take a very long time (up to 350 ms)
	 * and can be called with irqs disabled, reenable the irqs
	 * to let the other devices continue being serviced.
	 *
	 * It is safe doing so since our own interrupts will only be enabled
	 * in a subsequent step.
	 */
	local_save_flags(flags);
	local_irq_enable();

	rtlhal->fw_ready = false;
	rtlhal->hw_type = HARDWARE_TYPE_RTL8192CU;
	err = _rtl92cu_init_mac(hw);
	if (err) {
		pr_err("init mac failed!\n");
		goto exit;
	}
	err = rtl92c_download_fw(hw);
	if (err) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "Failed to download FW. Init HW without FW now..\n");
		err = 1;
		goto exit;
	}

	rtlhal->fw_ready = true;
	rtlhal->last_hmeboxnum = 0; /* h2c */
	_rtl92cu_phy_param_tab_init(hw);
	rtl92cu_phy_mac_config(hw);
	rtl92cu_phy_bb_config(hw);
	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	rtl92c_phy_rf_config(hw);
	if (IS_VENDOR_UMC_A_CUT(rtlhal->version) &&
	    !IS_92C_SERIAL(rtlhal->version)) {
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G1, MASKDWORD, 0x30255);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G2, MASKDWORD, 0x50a00);
	}
	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (enum radio_path)0,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (enum radio_path)1,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtl92cu_bb_block_on(hw);
	rtl_cam_reset_all_entry(hw);
	rtl92cu_enable_hw_security_config(hw);
	ppsc->rfpwr_state = ERFON;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	if (ppsc->rfpwr_state == ERFON) {
		rtl92c_phy_set_rfpath_switch(hw, 1);
		if (rtlphy->iqk_initialized) {
			rtl92c_phy_iq_calibrate(hw, true);
		} else {
			rtl92c_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		}
		rtl92c_dm_check_txpower_tracking(hw);
		rtl92c_phy_lc_calibrate(hw);
	}
	_rtl92cu_hw_configure(hw);
	_initpabias(hw);
	rtl92c_dm_init(hw);
exit:
	local_irq_restore(flags);
	return err;
}