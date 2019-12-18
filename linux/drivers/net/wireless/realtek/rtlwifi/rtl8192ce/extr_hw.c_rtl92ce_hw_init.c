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
typedef  int u8 ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; } ;
struct rtl_phy {int iqk_initialized; void** rfreg_chnlval; int /*<<< orphan*/  rf_mode; } ;
struct rtl_priv {TYPE_3__* intf_ops; TYPE_2__* cfg; struct rtl_phy phy; } ;
struct rtl_pci {int being_init_adapter; int receive_config; } ;
struct rtl_mac {int /*<<< orphan*/  mac_addr; } ;
struct rtl_hal {int fw_ready; int /*<<< orphan*/  version; scalar_t__ last_hmeboxnum; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable_aspm ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* disable_aspm ) (struct ieee80211_hw*) ;} ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BCCKEN ; 
 int BIT (int) ; 
 int BOFDMEN ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 scalar_t__ IS_81XXC_VENDOR_UMC_B_CUT (int /*<<< orphan*/ ) ; 
 int IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VENDOR_UMC_A_CUT (int /*<<< orphan*/ ) ; 
 int MASKDWORD ; 
 int RCR_ACRC32 ; 
 int RCR_AICV ; 
 int /*<<< orphan*/  REG_RCR ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF90_PATH_B ; 
 int /*<<< orphan*/  RFPGA0_ANALOGPARAMETER2 ; 
 int /*<<< orphan*/  RFPGA0_RFMOD ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int RF_IPA ; 
 int /*<<< orphan*/  RF_OP_BY_SW_3WIRE ; 
 int RF_RCK1 ; 
 int RF_RCK2 ; 
 int RF_RX_G1 ; 
 int RF_RX_G2 ; 
 int RF_SYN_G2 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl92ce_enable_aspm_back_door (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92ce_hw_configure (struct ieee80211_hw*) ; 
 int _rtl92ce_init_mac (struct ieee80211_hw*) ; 
 int efuse_read_1byte (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl8192ce_bt_hw_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_check_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_init (struct ieee80211_hw*) ; 
 int rtl92c_download_fw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_bb_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_iq_calibrate (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92c_phy_lc_calibrate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_mac_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_rf_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_set_rfpath_switch (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92ce_enable_hw_security_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_cam_reset_all_entry (struct ieee80211_hw*) ; 
 void* rtl_get_rfreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int rtl92ce_hw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	bool is92c;
	int err;
	u8 tmp_u1b;
	unsigned long flags;

	rtlpci->being_init_adapter = true;

	/* Since this function can take a very long time (up to 350 ms)
	 * and can be called with irqs disabled, reenable the irqs
	 * to let the other devices continue being serviced.
	 *
	 * It is safe doing so since our own interrupts will only be enabled
	 * in a subsequent step.
	 */
	local_save_flags(flags);
	local_irq_enable();

	rtlhal->fw_ready = false;
	rtlpriv->intf_ops->disable_aspm(hw);
	rtstatus = _rtl92ce_init_mac(hw);
	if (!rtstatus) {
		pr_err("Init MAC failed\n");
		err = 1;
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
	rtlhal->last_hmeboxnum = 0;
	rtl92c_phy_mac_config(hw);
	/* because last function modify RCR, so we update
	 * rcr var here, or TP will unstable for receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc for cisco 1252*/
	rtlpci->receive_config = rtl_read_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);
	rtl_write_dword(rtlpriv, REG_RCR, rtlpci->receive_config);
	rtl92c_phy_bb_config(hw);
	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	rtl92c_phy_rf_config(hw);
	if (IS_VENDOR_UMC_A_CUT(rtlhal->version) &&
	    !IS_92C_SERIAL(rtlhal->version)) {
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G1, MASKDWORD, 0x30255);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G2, MASKDWORD, 0x50a00);
	} else if (IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version)) {
		rtl_set_rfreg(hw, RF90_PATH_A, 0x0C, MASKDWORD, 0x894AE);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x0A, MASKDWORD, 0x1AF31);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_IPA, MASKDWORD, 0x8F425);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_SYN_G2, MASKDWORD, 0x4F200);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK1, MASKDWORD, 0x44053);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK2, MASKDWORD, 0x80201);
	}
	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (enum radio_path)0,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (enum radio_path)1,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 1);
	_rtl92ce_hw_configure(hw);
	rtl_cam_reset_all_entry(hw);
	rtl92ce_enable_hw_security_config(hw);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	_rtl92ce_enable_aspm_back_door(hw);
	rtlpriv->intf_ops->enable_aspm(hw);

	rtl8192ce_bt_hw_init(hw);

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

	is92c = IS_92C_SERIAL(rtlhal->version);
	tmp_u1b = efuse_read_1byte(hw, 0x1FA);
	if (!(tmp_u1b & BIT(0))) {
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0F, 0x05);
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "PA BIAS path A\n");
	}

	if (!(tmp_u1b & BIT(1)) && is92c) {
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0F, 0x05);
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "PA BIAS path B\n");
	}

	if (!(tmp_u1b & BIT(4))) {
		tmp_u1b = rtl_read_byte(rtlpriv, 0x16);
		tmp_u1b &= 0x0F;
		rtl_write_byte(rtlpriv, 0x16, tmp_u1b | 0x80);
		udelay(10);
		rtl_write_byte(rtlpriv, 0x16, tmp_u1b | 0x90);
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "under 1.5V\n");
	}
	rtl92c_dm_init(hw);
exit:
	local_irq_restore(flags);
	rtlpci->being_init_adapter = false;
	return err;
}