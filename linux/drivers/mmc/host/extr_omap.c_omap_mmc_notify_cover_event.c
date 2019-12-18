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
struct mmc_omap_slot {int cover_open; int /*<<< orphan*/  cover_tasklet; TYPE_2__* mmc; } ;
struct mmc_omap_host {int nr_slots; struct mmc_omap_slot** slots; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct mmc_omap_host* dev_get_drvdata (struct device*) ; 
 int mmc_omap_cover_is_open (struct mmc_omap_slot*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void omap_mmc_notify_cover_event(struct device *dev, int num, int is_closed)
{
	int cover_open;
	struct mmc_omap_host *host = dev_get_drvdata(dev);
	struct mmc_omap_slot *slot = host->slots[num];

	BUG_ON(num >= host->nr_slots);

	/* Other subsystems can call in here before we're initialised. */
	if (host->nr_slots == 0 || !host->slots[num])
		return;

	cover_open = mmc_omap_cover_is_open(slot);
	if (cover_open != slot->cover_open) {
		slot->cover_open = cover_open;
		sysfs_notify(&slot->mmc->class_dev.kobj, NULL, "cover_switch");
	}

	tasklet_hi_schedule(&slot->cover_tasklet);
}