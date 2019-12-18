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
struct arche_platform_drvdata {scalar_t__ wake_detect_state; int /*<<< orphan*/  wake_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WD_STATE_COLDBOOT_START ; 
 scalar_t__ WD_STATE_COLDBOOT_TRIG ; 
 int /*<<< orphan*/  WD_STATE_IDLE ; 
 int /*<<< orphan*/  apb_cold_boot ; 
 int /*<<< orphan*/  apb_poweroff ; 
 int /*<<< orphan*/  arche_platform_set_wake_detect_state (struct arche_platform_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb3613_hub_mode_ctrl (int) ; 

__attribute__((used)) static irqreturn_t arche_platform_wd_irq_thread(int irq, void *devid)
{
	struct arche_platform_drvdata *arche_pdata = devid;
	unsigned long flags;

	spin_lock_irqsave(&arche_pdata->wake_lock, flags);
	if (arche_pdata->wake_detect_state != WD_STATE_COLDBOOT_TRIG) {
		/* Something is wrong */
		spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);
		return IRQ_HANDLED;
	}

	arche_platform_set_wake_detect_state(arche_pdata,
					     WD_STATE_COLDBOOT_START);
	spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);

	/* It should complete power cycle, so first make sure it is poweroff */
	device_for_each_child(arche_pdata->dev, NULL, apb_poweroff);

	/* Bring APB out of reset: cold boot sequence */
	device_for_each_child(arche_pdata->dev, NULL, apb_cold_boot);

	/* Enable HUB3613 into HUB mode. */
	if (usb3613_hub_mode_ctrl(true))
		dev_warn(arche_pdata->dev, "failed to control hub device\n");

	spin_lock_irqsave(&arche_pdata->wake_lock, flags);
	arche_platform_set_wake_detect_state(arche_pdata, WD_STATE_IDLE);
	spin_unlock_irqrestore(&arche_pdata->wake_lock, flags);

	return IRQ_HANDLED;
}