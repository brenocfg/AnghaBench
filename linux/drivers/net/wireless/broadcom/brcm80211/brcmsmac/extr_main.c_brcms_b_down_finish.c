#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct brcms_hardware {int up; int sbclk; int clk; TYPE_5__* d11core; int /*<<< orphan*/  noreset; TYPE_2__* wlc; TYPE_1__* band; } ;
struct TYPE_9__ {int /*<<< orphan*/  bus; } ;
struct TYPE_8__ {int /*<<< orphan*/  wl; } ;
struct TYPE_7__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  OFF ; 
 scalar_t__ bcma_core_is_enabled (TYPE_5__*) ; 
 int /*<<< orphan*/  bcma_host_pci_down (int /*<<< orphan*/ ) ; 
 int bcma_read32 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_xtal (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_coredisable (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_c_flushqueues (TYPE_2__*) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (TYPE_2__*) ; 
 int brcms_deviceremoved (TYPE_2__*) ; 
 scalar_t__ brcms_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  wlc_phy_hw_clk_state_upd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_hw_state_upd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcms_b_down_finish(struct brcms_hardware *wlc_hw)
{
	uint callbacks = 0;
	bool dev_gone;

	if (!wlc_hw->up)
		return callbacks;

	wlc_hw->up = false;
	wlc_phy_hw_state_upd(wlc_hw->band->pi, false);

	dev_gone = brcms_deviceremoved(wlc_hw->wlc);

	if (dev_gone) {
		wlc_hw->sbclk = false;
		wlc_hw->clk = false;
		wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);

		/* reclaim any posted packets */
		brcms_c_flushqueues(wlc_hw->wlc);
	} else {

		/* Reset and disable the core */
		if (bcma_core_is_enabled(wlc_hw->d11core)) {
			if (bcma_read32(wlc_hw->d11core,
					D11REGOFFS(maccontrol)) & MCTL_EN_MAC)
				brcms_c_suspend_mac_and_wait(wlc_hw->wlc);
			callbacks += brcms_reset(wlc_hw->wlc->wl);
			brcms_c_coredisable(wlc_hw);
		}

		/* turn off primary xtal and pll */
		if (!wlc_hw->noreset) {
			bcma_host_pci_down(wlc_hw->d11core->bus);
			brcms_b_xtal(wlc_hw, OFF);
		}
	}

	return callbacks;
}