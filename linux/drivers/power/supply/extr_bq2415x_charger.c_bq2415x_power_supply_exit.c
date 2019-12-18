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
struct bq2415x_device {scalar_t__ automode; int /*<<< orphan*/  model; int /*<<< orphan*/  charger; int /*<<< orphan*/  work; scalar_t__ autotimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bq2415x_power_supply_exit(struct bq2415x_device *bq)
{
	bq->autotimer = 0;
	if (bq->automode > 0)
		bq->automode = 0;
	cancel_delayed_work_sync(&bq->work);
	power_supply_unregister(bq->charger);
	kfree(bq->model);
}