#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int raid_disks; int near_copies; } ;
struct r10conf {scalar_t__ fullsync; TYPE_4__* mddev; TYPE_1__ geo; int /*<<< orphan*/  device_lock; void* reshape_safe; void* reshape_progress; TYPE_1__ prev; } ;
struct TYPE_8__ {int chunk_sectors; TYPE_3__* queue; int /*<<< orphan*/  recovery; } ;
struct TYPE_7__ {TYPE_2__* backing_dev_info; } ;
struct TYPE_6__ {int ra_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 void* MaxSector ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  md_finish_reshape (TYPE_4__*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void end_reshape(struct r10conf *conf)
{
	if (test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery))
		return;

	spin_lock_irq(&conf->device_lock);
	conf->prev = conf->geo;
	md_finish_reshape(conf->mddev);
	smp_wmb();
	conf->reshape_progress = MaxSector;
	conf->reshape_safe = MaxSector;
	spin_unlock_irq(&conf->device_lock);

	/* read-ahead size must cover two whole stripes, which is
	 * 2 * (datadisks) * chunksize where 'n' is the number of raid devices
	 */
	if (conf->mddev->queue) {
		int stripe = conf->geo.raid_disks *
			((conf->mddev->chunk_sectors << 9) / PAGE_SIZE);
		stripe /= conf->geo.near_copies;
		if (conf->mddev->queue->backing_dev_info->ra_pages < 2 * stripe)
			conf->mddev->queue->backing_dev_info->ra_pages = 2 * stripe;
	}
	conf->fullsync = 0;
}