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
typedef  int u32 ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; } ;
struct TYPE_4__ {int fw_current_inpsmode; } ;
struct rtl_phy {int /*<<< orphan*/  current_channel; void** rfreg_chnlval; int /*<<< orphan*/  rf_mode; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ psc; struct rtl_phy phy; } ;
struct rtl_pci {int being_init_adapter; int init_ready; int receive_config; } ;
struct rtl_mac {int /*<<< orphan*/  mac_addr; scalar_t__ rdg_en; } ;
struct rtl_hal {scalar_t__ current_bandtype; scalar_t__ interfaceindex; scalar_t__ macphymode; scalar_t__ earlymode_enable; scalar_t__ last_hmeboxnum; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 int BCCKEN ; 
 int BIT (int) ; 
 int BOFDMEN ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 scalar_t__ DUALMAC_DUALPHY ; 
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  MAX_STALL_TIME ; 
 int RCR_ACRC32 ; 
 int RCR_AICV ; 
 int /*<<< orphan*/  REG_RCR ; 
 int REG_RD_CTRL ; 
 int /*<<< orphan*/  REG_RD_NAV_NXT ; 
 int REG_RD_RESP_PKT_TH ; 
 scalar_t__ RF90_PATH_A ; 
 int /*<<< orphan*/  RFPGA0_ANALOGPARAMETER2 ; 
 int /*<<< orphan*/  RFPGA0_ANALOGPARAMETER4 ; 
 int /*<<< orphan*/  RFPGA0_RFMOD ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int RF_CHNLBW ; 
 int /*<<< orphan*/  RF_OP_BY_SW_3WIRE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl92de_enable_aspm_back_door (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92de_hw_configure (struct ieee80211_hw*) ; 
 int _rtl92de_init_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  globalmutex_for_power_and_efuse ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl92d_dm_init (struct ieee80211_hw*) ; 
 int rtl92d_download_fw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_bb_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_get_hw_reg_originalvalue (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_lc_calibrate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_mac_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_reset_iqk_result (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_rf_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92d_phy_set_txpower_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92d_update_bbrf_configuration (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92de_enable_hw_security_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_cam_reset_all_entry (struct ieee80211_hw*) ; 
 void* rtl_get_rfreg (struct ieee80211_hw*,int,int,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

int rtl92de_hw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool rtstatus = true;
	u8 tmp_u1b;
	int i;
	int err;
	unsigned long flags;

	rtlpci->being_init_adapter = true;
	rtlpci->init_ready = false;
	spin_lock_irqsave(&globalmutex_for_power_and_efuse, flags);
	/* we should do iqk after disable/enable */
	rtl92d_phy_reset_iqk_result(hw);
	/* rtlpriv->intf_ops->disable_aspm(hw); */
	rtstatus = _rtl92de_init_mac(hw);
	if (!rtstatus) {
		pr_err("Init MAC failed\n");
		err = 1;
		spin_unlock_irqrestore(&globalmutex_for_power_and_efuse, flags);
		return err;
	}
	err = rtl92d_download_fw(hw);
	spin_unlock_irqrestore(&globalmutex_for_power_and_efuse, flags);
	if (err) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "Failed to download FW. Init HW without FW..\n");
		return 1;
	}
	rtlhal->last_hmeboxnum = 0;
	rtlpriv->psc.fw_current_inpsmode = false;

	tmp_u1b = rtl_read_byte(rtlpriv, 0x605);
	tmp_u1b = tmp_u1b | 0x30;
	rtl_write_byte(rtlpriv, 0x605, tmp_u1b);

	if (rtlhal->earlymode_enable) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "EarlyMode Enabled!!!\n");

		tmp_u1b = rtl_read_byte(rtlpriv, 0x4d0);
		tmp_u1b = tmp_u1b | 0x1f;
		rtl_write_byte(rtlpriv, 0x4d0, tmp_u1b);

		rtl_write_byte(rtlpriv, 0x4d3, 0x80);

		tmp_u1b = rtl_read_byte(rtlpriv, 0x605);
		tmp_u1b = tmp_u1b | 0x40;
		rtl_write_byte(rtlpriv, 0x605, tmp_u1b);
	}

	if (mac->rdg_en) {
		rtl_write_byte(rtlpriv, REG_RD_CTRL, 0xff);
		rtl_write_word(rtlpriv, REG_RD_NAV_NXT, 0x200);
		rtl_write_byte(rtlpriv, REG_RD_RESP_PKT_TH, 0x05);
	}

	rtl92d_phy_mac_config(hw);
	/* because last function modify RCR, so we update
	 * rcr var here, or TP will unstable for receive_config
	 * is wrong, RX RCR_ACRC32 will cause TP unstabel & Rx
	 * RCR_APP_ICV will cause mac80211 unassoc for cisco 1252*/
	rtlpci->receive_config = rtl_read_dword(rtlpriv, REG_RCR);
	rtlpci->receive_config &= ~(RCR_ACRC32 | RCR_AICV);

	rtl92d_phy_bb_config(hw);

	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	/* set before initialize RF */
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0xf);

	/* config RF */
	rtl92d_phy_rf_config(hw);

	/* After read predefined TXT, we must set BB/MAC/RF
	 * register as our requirement */
	/* After load BB,RF params,we need do more for 92D. */
	rtl92d_update_bbrf_configuration(hw);
	/* set default value after initialize RF,  */
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0);
	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (enum radio_path)0,
			RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (enum radio_path)1,
			RF_CHNLBW, RFREG_OFFSET_MASK);

	/*---- Set CCK and OFDM Block "ON"----*/
	if (rtlhal->current_bandtype == BAND_ON_2_4G)
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);
	if (rtlhal->interfaceindex == 0) {
		/* RFPGA0_ANALOGPARAMETER2: cck clock select,
		 *  set to 20MHz by default */
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10) |
			      BIT(11), 3);
	} else {
		/* Mac1 */
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(11) |
			      BIT(10), 3);
	}

	_rtl92de_hw_configure(hw);

	/* reset hw sec */
	rtl_cam_reset_all_entry(hw);
	rtl92de_enable_hw_security_config(hw);

	/* Read EEPROM TX power index and PHY_REG_PG.txt to capture correct */
	/* TX power index for different rate set. */
	rtl92d_phy_get_hw_reg_originalvalue(hw);
	rtl92d_phy_set_txpower_level(hw, rtlphy->current_channel);

	ppsc->rfpwr_state = ERFON;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);

	_rtl92de_enable_aspm_back_door(hw);
	/* rtlpriv->intf_ops->enable_aspm(hw); */

	rtl92d_dm_init(hw);
	rtlpci->being_init_adapter = false;

	if (ppsc->rfpwr_state == ERFON) {
		rtl92d_phy_lc_calibrate(hw);
		/* 5G and 2.4G must wait sometime to let RF LO ready */
		if (rtlhal->macphymode == DUALMAC_DUALPHY) {
			u32 tmp_rega;
			for (i = 0; i < 10000; i++) {
				udelay(MAX_STALL_TIME);

				tmp_rega = rtl_get_rfreg(hw,
						  (enum radio_path)RF90_PATH_A,
						  0x2a, MASKDWORD);

				if (((tmp_rega & BIT(11)) == BIT(11)))
					break;
			}
			/* check that loop was successful. If not, exit now */
			if (i == 10000) {
				rtlpci->init_ready = false;
				return 1;
			}
		}
	}
	rtlpci->init_ready = true;
	return err;
}