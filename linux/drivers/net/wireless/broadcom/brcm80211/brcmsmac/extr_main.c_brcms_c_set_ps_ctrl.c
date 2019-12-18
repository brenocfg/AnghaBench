#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct brcms_c_info {TYPE_2__* hw; TYPE_1__* pub; } ;
struct TYPE_5__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_4__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_HPS ; 
 int MCTL_WAKE ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_mctrl (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  brcms_b_wait_for_wake (TYPE_2__*) ; 
 int brcms_c_ps_allowed (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_dbg_mac80211 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  maccontrol ; 

__attribute__((used)) static void brcms_c_set_ps_ctrl(struct brcms_c_info *wlc)
{
	u32 v1, v2;
	bool hps;
	bool awake_before;

	hps = brcms_c_ps_allowed(wlc);

	brcms_dbg_mac80211(wlc->hw->d11core, "wl%d: hps %d\n", wlc->pub->unit,
			   hps);

	v1 = bcma_read32(wlc->hw->d11core, D11REGOFFS(maccontrol));
	v2 = MCTL_WAKE;
	if (hps)
		v2 |= MCTL_HPS;

	brcms_b_mctrl(wlc->hw, MCTL_WAKE | MCTL_HPS, v2);

	awake_before = ((v1 & MCTL_WAKE) || ((v1 & MCTL_HPS) == 0));

	if (!awake_before)
		brcms_b_wait_for_wake(wlc->hw);
}