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
struct mv_otg {int /*<<< orphan*/  work; int /*<<< orphan*/  qwork; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mv_otg_run_state_machine(struct mv_otg *mvotg,
				     unsigned long delay)
{
	dev_dbg(&mvotg->pdev->dev, "transceiver is updated\n");
	if (!mvotg->qwork)
		return;

	queue_delayed_work(mvotg->qwork, &mvotg->work, delay);
}