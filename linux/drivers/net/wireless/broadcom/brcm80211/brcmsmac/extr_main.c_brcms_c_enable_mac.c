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
typedef  int u32 ;
struct brcms_hardware {scalar_t__ mac_suspend_depth; int /*<<< orphan*/  unit; struct bcma_device* d11core; } ;
struct brcms_c_info {TYPE_1__* band; struct brcms_hardware* hw; } ;
struct bcma_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bandunit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_WAKE_OVERRIDE_MACSUSPEND ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 int MCTL_PSM_JMP_0 ; 
 int MCTL_PSM_RUN ; 
 int MI_MACSSPNDD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_b_mctrl (struct brcms_hardware*,int,int) ; 
 int /*<<< orphan*/  brcms_c_ucode_wake_override_clear (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_mac80211 (struct bcma_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  macintstatus ; 

void brcms_c_enable_mac(struct brcms_c_info *wlc)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	struct bcma_device *core = wlc_hw->d11core;
	u32 mc, mi;

	brcms_dbg_mac80211(core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   wlc->band->bandunit);

	/*
	 * Track overlapping suspend requests
	 */
	wlc_hw->mac_suspend_depth--;
	if (wlc_hw->mac_suspend_depth > 0)
		return;

	mc = bcma_read32(core, D11REGOFFS(maccontrol));
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(mc & MCTL_EN_MAC);
	WARN_ON(!(mc & MCTL_PSM_RUN));

	brcms_b_mctrl(wlc_hw, MCTL_EN_MAC, MCTL_EN_MAC);
	bcma_write32(core, D11REGOFFS(macintstatus), MI_MACSSPNDD);

	mc = bcma_read32(core, D11REGOFFS(maccontrol));
	WARN_ON(mc & MCTL_PSM_JMP_0);
	WARN_ON(!(mc & MCTL_EN_MAC));
	WARN_ON(!(mc & MCTL_PSM_RUN));

	mi = bcma_read32(core, D11REGOFFS(macintstatus));
	WARN_ON(mi & MI_MACSSPNDD);

	brcms_c_ucode_wake_override_clear(wlc_hw,
					  BRCMS_WAKE_OVERRIDE_MACSUSPEND);
}