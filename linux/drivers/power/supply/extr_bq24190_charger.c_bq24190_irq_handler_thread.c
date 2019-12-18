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
struct bq24190_dev_info {int irq_event; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  bq24190_check_status (struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bq24190_irq_handler_thread(int irq, void *data)
{
	struct bq24190_dev_info *bdi = data;
	int error;

	bdi->irq_event = true;
	error = pm_runtime_get_sync(bdi->dev);
	if (error < 0) {
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", error);
		pm_runtime_put_noidle(bdi->dev);
		return IRQ_NONE;
	}
	bq24190_check_status(bdi);
	pm_runtime_mark_last_busy(bdi->dev);
	pm_runtime_put_autosuspend(bdi->dev);
	bdi->irq_event = false;

	return IRQ_HANDLED;
}