#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int u32 ;
struct brcms_hardware {TYPE_1__* band; int /*<<< orphan*/  d11core; int /*<<< orphan*/  unit; } ;
struct brcms_c_info {int /*<<< orphan*/  wl; struct brcms_hardware* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_core_phy_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_setxband (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_mac80211 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int brcms_intrsoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  wlc_phy_switch_radio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 brcms_c_setband_inact(struct brcms_c_info *wlc, uint bandunit)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	u32 macintmask;
	u32 macctrl;

	brcms_dbg_mac80211(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);
	macctrl = bcma_read32(wlc_hw->d11core,
			      D11REGOFFS(maccontrol));
	WARN_ON((macctrl & MCTL_EN_MAC) != 0);

	/* disable interrupts */
	macintmask = brcms_intrsoff(wlc->wl);

	/* radio off */
	wlc_phy_switch_radio(wlc_hw->band->pi, OFF);

	brcms_b_core_phy_clk(wlc_hw, OFF);

	brcms_c_setxband(wlc_hw, bandunit);

	return macintmask;
}