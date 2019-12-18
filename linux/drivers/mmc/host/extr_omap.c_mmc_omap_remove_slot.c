#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_omap_slot {TYPE_1__* host; int /*<<< orphan*/  cover_timer; int /*<<< orphan*/  cover_tasklet; TYPE_2__* pdata; struct mmc_host* mmc; } ;
struct mmc_host {int /*<<< orphan*/  class_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * get_cover_state; int /*<<< orphan*/ * name; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmc_omap_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_cover_switch ; 
 int /*<<< orphan*/  dev_attr_slot_name ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_omap_remove_slot(struct mmc_omap_slot *slot)
{
	struct mmc_host *mmc = slot->mmc;

	if (slot->pdata->name != NULL)
		device_remove_file(&mmc->class_dev, &dev_attr_slot_name);
	if (slot->pdata->get_cover_state != NULL)
		device_remove_file(&mmc->class_dev, &dev_attr_cover_switch);

	tasklet_kill(&slot->cover_tasklet);
	del_timer_sync(&slot->cover_timer);
	flush_workqueue(slot->host->mmc_omap_wq);

	mmc_remove_host(mmc);
	mmc_free_host(mmc);
}