#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock_queue; int /*<<< orphan*/ * file_priv; int /*<<< orphan*/ * hw_lock; } ;
struct drm_master {TYPE_3__ lock; int /*<<< orphan*/  magic_map; } ;
struct drm_file {struct drm_master* master; scalar_t__ is_master; scalar_t__ magic; TYPE_1__* minor; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lock; } ;
struct drm_device {int /*<<< orphan*/  master_mutex; struct drm_master* master; int /*<<< orphan*/  struct_mutex; TYPE_2__ sigdata; } ;
struct TYPE_4__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_drop_master (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_is_current_master (struct drm_file*) ; 
 int /*<<< orphan*/  drm_lease_revoke (struct drm_master*) ; 
 int /*<<< orphan*/  drm_master_put (struct drm_master**) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void drm_master_release(struct drm_file *file_priv)
{
	struct drm_device *dev = file_priv->minor->dev;
	struct drm_master *master = file_priv->master;

	mutex_lock(&dev->master_mutex);
	if (file_priv->magic)
		idr_remove(&file_priv->master->magic_map, file_priv->magic);

	if (!drm_is_current_master(file_priv))
		goto out;

	if (drm_core_check_feature(dev, DRIVER_LEGACY)) {
		/*
		 * Since the master is disappearing, so is the
		 * possibility to lock.
		 */
		mutex_lock(&dev->struct_mutex);
		if (master->lock.hw_lock) {
			if (dev->sigdata.lock == master->lock.hw_lock)
				dev->sigdata.lock = NULL;
			master->lock.hw_lock = NULL;
			master->lock.file_priv = NULL;
			wake_up_interruptible_all(&master->lock.lock_queue);
		}
		mutex_unlock(&dev->struct_mutex);
	}

	if (dev->master == file_priv->master)
		drm_drop_master(dev, file_priv);
out:
	if (drm_core_check_feature(dev, DRIVER_MODESET) && file_priv->is_master) {
		/* Revoke any leases held by this or lessees, but only if
		 * this is the "real" master
		 */
		drm_lease_revoke(master);
	}

	/* drop the master reference held by the file priv */
	if (file_priv->master)
		drm_master_put(&file_priv->master);
	mutex_unlock(&dev->master_mutex);
}