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
struct rtl_ps_ctl {scalar_t__ rfoff_reason; } ;
struct TYPE_6__ {int interfaceindex; } ;
struct rtl_priv {TYPE_3__ rtlhal; TYPE_2__* cfg; } ;
struct rtl_pci {scalar_t__ driver_is_goingto_unload; } ;
struct rtl_mac {int /*<<< orphan*/  link_state; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BDWORD ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  MAC80211_NOLINK ; 
 int MASKBYTE0 ; 
 int NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ REG_APSD_CTRL ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_PCIE_CTRL_REG ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RFPGA0_ANALOGPARAMETER4 ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  ROFDM0_TRXPATHENABLE ; 
 int /*<<< orphan*/  ROFDM1_TRXPATHENABLE ; 
 int /*<<< orphan*/  RT_RF_OFF_LEVL_HALT_NIC ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl92de_poweroff_adapter (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92de_set_media_status (struct ieee80211_hw*,int) ; 
 scalar_t__ rtl92d_phy_check_poweroff (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl92de_card_disable(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	enum nl80211_iftype opmode;

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl92de_set_media_status(hw, opmode);

	if (rtlpci->driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	/* Power sequence for each MAC. */
	/* a. stop tx DMA  */
	/* b. close RF */
	/* c. clear rx buf */
	/* d. stop rx DMA */
	/* e.  reset MAC */

	/* a. stop tx DMA */
	rtl_write_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xFE);
	udelay(50);

	/* b. TXPAUSE 0x522[7:0] = 0xFF Pause MAC TX queue */

	/* c. ========RF OFF sequence==========  */
	/* 0x88c[23:20] = 0xf. */
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0xf);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);

	/* APSD_CTRL 0x600[7:0] = 0x40 */
	rtl_write_byte(rtlpriv, REG_APSD_CTRL, 0x40);

	/* Close antenna 0,0xc04,0xd04 */
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKBYTE0, 0);
	rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE, BDWORD, 0);

	/*  SYS_FUNC_EN 0x02[7:0] = 0xE2   reset BB state machine */
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);

	/* Mac0 can not do Global reset. Mac1 can do. */
	/* SYS_FUNC_EN 0x02[7:0] = 0xE0  reset BB state machine  */
	if (rtlpriv->rtlhal.interfaceindex == 1)
		rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE0);
	udelay(50);

	/* d.  stop tx/rx dma before disable REG_CR (0x100) to fix */
	/* dma hang issue when disable/enable device.  */
	rtl_write_byte(rtlpriv, REG_PCIE_CTRL_REG + 1, 0xff);
	udelay(50);
	rtl_write_byte(rtlpriv, REG_CR, 0x0);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "==> Do power off.......\n");
	if (rtl92d_phy_check_poweroff(hw))
		_rtl92de_poweroff_adapter(hw);
	return;
}