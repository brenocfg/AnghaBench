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
struct ab8500_btemp {int /*<<< orphan*/  btemp_periodic_work; int /*<<< orphan*/  btemp_wq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_btemp_periodic(struct ab8500_btemp *di,
	bool enable)
{
	dev_dbg(di->dev, "Enable periodic temperature measurements: %d\n",
		enable);
	/*
	 * Make sure a new measurement is done directly by cancelling
	 * any pending work
	 */
	cancel_delayed_work_sync(&di->btemp_periodic_work);

	if (enable)
		queue_delayed_work(di->btemp_wq, &di->btemp_periodic_work, 0);
}