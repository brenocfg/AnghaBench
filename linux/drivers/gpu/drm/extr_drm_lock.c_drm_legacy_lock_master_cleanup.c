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
struct TYPE_3__ {int /*<<< orphan*/  lock_queue; int /*<<< orphan*/ * file_priv; int /*<<< orphan*/ * hw_lock; } ;
struct drm_master {TYPE_1__ lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lock; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__ sigdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void drm_legacy_lock_master_cleanup(struct drm_device *dev, struct drm_master *master)
{
	if (!drm_core_check_feature(dev, DRIVER_LEGACY))
		return;

	/*
	 * Since the master is disappearing, so is the
	 * possibility to lock.
	 */	mutex_lock(&dev->struct_mutex);
	if (master->lock.hw_lock) {
		if (dev->sigdata.lock == master->lock.hw_lock)
			dev->sigdata.lock = NULL;
		master->lock.hw_lock = NULL;
		master->lock.file_priv = NULL;
		wake_up_interruptible_all(&master->lock.lock_queue);
	}
	mutex_unlock(&dev->struct_mutex);
}