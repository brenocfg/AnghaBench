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
struct rtl_usb {int* irq_mask; int disablehwsm; int /*<<< orphan*/  acm_method; } ;
struct rtl_ps_ctl {int inactiveps; int leisure_ps; int fwctrl_lps; int reg_fwctrl_lps; int reg_max_lps_awakeintvl; int /*<<< orphan*/  fwctrl_psmode; } ;
struct rtl_mac {int beacon_interval; int current_ampdu_density; int current_ampdu_factor; scalar_t__ max_mss_density; scalar_t__ min_space_cfg; } ;
struct rtl_hal {struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACMWAY2_SW ; 
 int /*<<< orphan*/  FW_PS_DTIM_MODE ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (int /*<<< orphan*/ ) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl_usb_init_sw(struct ieee80211_hw *hw)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	rtlhal->hw = hw;
	ppsc->inactiveps = false;
	ppsc->leisure_ps = false;
	ppsc->fwctrl_lps = false;
	ppsc->reg_fwctrl_lps = 3;
	ppsc->reg_max_lps_awakeintvl = 5;
	ppsc->fwctrl_psmode = FW_PS_DTIM_MODE;

	 /* IBSS */
	mac->beacon_interval = 100;

	 /* AMPDU */
	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;

	/* set sane AMPDU defaults */
	mac->current_ampdu_density = 7;
	mac->current_ampdu_factor = 3;

	/* QOS */
	rtlusb->acm_method = EACMWAY2_SW;

	/* IRQ */
	/* HIMR - turn all on */
	rtlusb->irq_mask[0] = 0xFFFFFFFF;
	/* HIMR_EX - turn all on */
	rtlusb->irq_mask[1] = 0xFFFFFFFF;
	rtlusb->disablehwsm =  true;
}