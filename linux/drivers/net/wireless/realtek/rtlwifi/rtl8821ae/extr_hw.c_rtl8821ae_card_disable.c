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
typedef  int u8 ;
typedef  int u32 ;
struct rtl_ps_ctl {scalar_t__ rfoff_reason; } ;
struct TYPE_10__ {int iqk_initialized; } ;
struct TYPE_7__ {scalar_t__ driver_is_goingto_unload; } ;
struct rtl_priv {TYPE_5__ phy; TYPE_4__* cfg; TYPE_2__ rtlhal; TYPE_1__* intf_ops; } ;
struct rtl_mac {scalar_t__ opmode; scalar_t__ link_state; } ;
struct rtl_hal {int re_init_llt_table; scalar_t__ hw_rof_enable; scalar_t__ enter_pnp_sleep; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_9__ {TYPE_3__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* reset_trx_ring ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  HAL_DEF_WOWLAN ; 
 int /*<<< orphan*/  HW_VAR_AID ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MAC80211_NOLINK ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ REG_APS_FSMCO ; 
 scalar_t__ REG_HSISR ; 
 scalar_t__ REG_MCUTST_WOWLAN ; 
 scalar_t__ REG_PCIE_CTRL_REG ; 
 scalar_t__ REG_RSV_CTRL ; 
 scalar_t__ REG_RXDMA_CONTROL ; 
 scalar_t__ REG_SYS_CLKR ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  RT_MEDIA_CONNECT ; 
 int /*<<< orphan*/  RT_RF_OFF_LEVL_HALT_NIC ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8821ae_clear_pci_pme_status (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8821ae_download_rsvd_page (struct ieee80211_hw*,int) ; 
 scalar_t__ _rtl8821ae_dynamic_rqpn (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  _rtl8821ae_poweroff_adapter (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8821ae_set_media_status (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_disconnect_decision_ctrl_cmd (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_global_info_cmd (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_keep_alive_cmd (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_media_status_rpt_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_related_for_wowlan (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_remote_wake_ctrl_cmd (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_set_fw_wowlan_mode (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl8821ae_card_disable(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	enum nl80211_iftype opmode;
	bool support_remote_wakeup;
	u8 tmp;
	u32 count = 0;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));

	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

	if (!(support_remote_wakeup && mac->opmode == NL80211_IFTYPE_STATION)
	    || !rtlhal->enter_pnp_sleep) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Normal Power off\n");
		mac->link_state = MAC80211_NOLINK;
		opmode = NL80211_IFTYPE_UNSPECIFIED;
		_rtl8821ae_set_media_status(hw, opmode);
		_rtl8821ae_poweroff_adapter(hw);
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Wowlan Supported.\n");
		/* 3 <1> Prepare for configuring wowlan related infomations */
		/* Clear Fw WoWLAN event. */
		rtl_write_byte(rtlpriv, REG_MCUTST_WOWLAN, 0x0);

#if (USE_SPECIFIC_FW_TO_SUPPORT_WOWLAN == 1)
		rtl8821ae_set_fw_related_for_wowlan(hw, true);
#endif
		/* Dynamically adjust Tx packet boundary
		 * for download reserved page packet.
		 * reserve 30 pages for rsvd page */
		if (_rtl8821ae_dynamic_rqpn(hw, 0xE0, 0x3, 0x80c20d0d))
			rtlhal->re_init_llt_table = true;

		/* 3 <2> Set Fw releted H2C cmd. */

		/* Set WoWLAN related security information. */
		rtl8821ae_set_fw_global_info_cmd(hw);

		_rtl8821ae_download_rsvd_page(hw, true);

		/* Just enable AOAC related functions when we connect to AP. */
		printk("mac->link_state = %d\n", mac->link_state);
		if (mac->link_state >= MAC80211_LINKED &&
		    mac->opmode == NL80211_IFTYPE_STATION) {
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AID, NULL);
			rtl8821ae_set_fw_media_status_rpt_cmd(hw,
							      RT_MEDIA_CONNECT);

			rtl8821ae_set_fw_wowlan_mode(hw, true);
			/* Enable Fw Keep alive mechanism. */
			rtl8821ae_set_fw_keep_alive_cmd(hw, true);

			/* Enable disconnect decision control. */
			rtl8821ae_set_fw_disconnect_decision_ctrl_cmd(hw, true);
		}

		/* 3 <3> Hw Configutations */

		/* Wait untill Rx DMA Finished before host sleep.
		 * FW Pause Rx DMA may happens when received packet doing dma.
		 */
		rtl_write_byte(rtlpriv, REG_RXDMA_CONTROL, BIT(2));

		tmp = rtl_read_byte(rtlpriv, REG_RXDMA_CONTROL);
		count = 0;
		while (!(tmp & BIT(1)) && (count++ < 100)) {
			udelay(10);
			tmp = rtl_read_byte(rtlpriv, REG_RXDMA_CONTROL);
		}
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Wait Rx DMA Finished before host sleep. count=%d\n",
			  count);

		/* reset trx ring */
		rtlpriv->intf_ops->reset_trx_ring(hw);

		rtl_write_byte(rtlpriv, REG_APS_FSMCO + 1, 0x0);

		_rtl8821ae_clear_pci_pme_status(hw);
		tmp = rtl_read_byte(rtlpriv, REG_SYS_CLKR);
		rtl_write_byte(rtlpriv, REG_SYS_CLKR, tmp | BIT(3));
		/* prevent 8051 to be reset by PERST */
		rtl_write_byte(rtlpriv, REG_RSV_CTRL, 0x20);
		rtl_write_byte(rtlpriv, REG_RSV_CTRL, 0x60);
	}

	if (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	/* For wowlan+LPS+32k. */
	if (support_remote_wakeup && rtlhal->enter_pnp_sleep) {
		/* Set the WoWLAN related function control enable.
		 * It should be the last H2C cmd in the WoWLAN flow. */
		rtl8821ae_set_fw_remote_wake_ctrl_cmd(hw, 1);

		/* Stop Pcie Interface Tx DMA. */
		rtl_write_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xff);
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "Stop PCIE Tx DMA.\n");

		/* Wait for TxDMA idle. */
		count = 0;
		do {
			tmp = rtl_read_byte(rtlpriv, REG_PCIE_CTRL_REG);
			udelay(10);
			count++;
		} while ((tmp != 0) && (count < 100));
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Wait Tx DMA Finished before host sleep. count=%d\n",
			  count);

		if (rtlhal->hw_rof_enable) {
			printk("hw_rof_enable\n");
			tmp = rtl_read_byte(rtlpriv, REG_HSISR + 3);
			rtl_write_byte(rtlpriv, REG_HSISR + 3, tmp | BIT(1));
		}
	}
	/* after power off we should do iqk again */
	rtlpriv->phy.iqk_initialized = false;
}