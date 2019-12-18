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
struct ab8500_fg {int /*<<< orphan*/  fg_check_hw_failure_work; int /*<<< orphan*/  fg_wq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ab8500_fg_batt_ovv_handler(int irq, void *_di)
{
	struct ab8500_fg *di = _di;

	dev_dbg(di->dev, "Battery OVV\n");

	/* Schedule a new HW failure check */
	queue_delayed_work(di->fg_wq, &di->fg_check_hw_failure_work, 0);

	return IRQ_HANDLED;
}