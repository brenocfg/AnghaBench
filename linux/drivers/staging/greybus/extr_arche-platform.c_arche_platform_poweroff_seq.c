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
struct arche_platform_drvdata {scalar_t__ state; int /*<<< orphan*/  is_reset_act_hi; int /*<<< orphan*/  svc_reset; int /*<<< orphan*/  svc_ref_clk; int /*<<< orphan*/  wake_lock; int /*<<< orphan*/  wake_detect_irq; } ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 scalar_t__ ARCHE_PLATFORM_STATE_OFF ; 
 int /*<<< orphan*/  WD_STATE_IDLE ; 
 int /*<<< orphan*/  arche_platform_set_state (struct arche_platform_drvdata*,scalar_t__) ; 
 int /*<<< orphan*/  arche_platform_set_wake_detect_state (struct arche_platform_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  svc_reset_onoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arche_platform_poweroff_seq(struct arche_platform_drvdata *arche_pdata)
{
	unsigned long flags;

	if (arche_pdata->state == ARCHE_PLATFORM_STATE_OFF)
		return;

	/* If in fw_flashing mode, then no need to repeate things again */
	if (arche_pdata->state != ARCHE_PLATFORM_STATE_FW_FLASHING) {
		disable_irq(arche_pdata->wake_detect_irq);

		spin_lock_irqsave(&arche_pdata->wake_lock, flags);
		arche_platform_set_wake_detect_state(arche_pdata,
						     WD_STATE_IDLE);
		spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);
	}

	clk_disable_unprepare(arche_pdata->svc_ref_clk);

	/* As part of exit, put APB back in reset state */
	svc_reset_onoff(arche_pdata->svc_reset,	arche_pdata->is_reset_act_hi);

	arche_platform_set_state(arche_pdata, ARCHE_PLATFORM_STATE_OFF);
}