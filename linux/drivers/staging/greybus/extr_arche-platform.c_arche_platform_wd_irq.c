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
struct arche_platform_drvdata {scalar_t__ wake_detect_state; int /*<<< orphan*/  wake_lock; scalar_t__ wake_detect_start; int /*<<< orphan*/  wake_detect; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  WD_COLDBOOT_PULSE_WIDTH_MS ; 
 scalar_t__ WD_STATE_BOOT_INIT ; 
 scalar_t__ WD_STATE_COLDBOOT_START ; 
 scalar_t__ WD_STATE_COLDBOOT_TRIG ; 
 scalar_t__ WD_STATE_IDLE ; 
 int /*<<< orphan*/  arche_platform_set_wake_detect_state (struct arche_platform_drvdata*,scalar_t__) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static irqreturn_t arche_platform_wd_irq(int irq, void *devid)
{
	struct arche_platform_drvdata *arche_pdata = devid;
	unsigned long flags;

	spin_lock_irqsave(&arche_pdata->wake_lock, flags);

	if (gpiod_get_value(arche_pdata->wake_detect)) {
		/* wake/detect rising */

		/*
		 * If wake/detect line goes high after low, within less than
		 * 30msec, then standby boot sequence is initiated, which is not
		 * supported/implemented as of now. So ignore it.
		 */
		if (arche_pdata->wake_detect_state == WD_STATE_BOOT_INIT) {
			if (time_before(jiffies,
					arche_pdata->wake_detect_start +
					msecs_to_jiffies(WD_COLDBOOT_PULSE_WIDTH_MS))) {
				arche_platform_set_wake_detect_state(arche_pdata,
								     WD_STATE_IDLE);
			} else {
				/*
				 * Check we are not in middle of irq thread
				 * already
				 */
				if (arche_pdata->wake_detect_state !=
						WD_STATE_COLDBOOT_START) {
					arche_platform_set_wake_detect_state(arche_pdata,
									     WD_STATE_COLDBOOT_TRIG);
					spin_unlock_irqrestore(
						&arche_pdata->wake_lock,
						flags);
					return IRQ_WAKE_THREAD;
				}
			}
		}
	} else {
		/* wake/detect falling */
		if (arche_pdata->wake_detect_state == WD_STATE_IDLE) {
			arche_pdata->wake_detect_start = jiffies;
			/*
			 * In the beginning, when wake/detect goes low
			 * (first time), we assume it is meant for coldboot
			 * and set the flag. If wake/detect line stays low
			 * beyond 30msec, then it is coldboot else fallback
			 * to standby boot.
			 */
			arche_platform_set_wake_detect_state(arche_pdata,
							     WD_STATE_BOOT_INIT);
		}
	}

	spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);

	return IRQ_HANDLED;
}