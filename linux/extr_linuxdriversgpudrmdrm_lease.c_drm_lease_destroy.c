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
struct drm_master {scalar_t__ lessee_id; scalar_t__ lessor; int /*<<< orphan*/  lessee_list; int /*<<< orphan*/  lessees; struct drm_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idr_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  lessee_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_LEASE (char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__* drm_lease_owner (struct drm_master*) ; 
 int /*<<< orphan*/  drm_master_put (scalar_t__*) ; 
 int /*<<< orphan*/  drm_sysfs_lease_event (struct drm_device*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_lease_destroy(struct drm_master *master)
{
	struct drm_device *dev = master->dev;

	mutex_lock(&dev->mode_config.idr_mutex);

	DRM_DEBUG_LEASE("drm_lease_destroy %d\n", master->lessee_id);

	/* This master is referenced by all lessees, hence it cannot be destroyed
	 * until all of them have been
	 */
	WARN_ON(!list_empty(&master->lessees));

	/* Remove this master from the lessee idr in the owner */
	if (master->lessee_id != 0) {
		DRM_DEBUG_LEASE("remove master %d from device list of lessees\n", master->lessee_id);
		idr_remove(&(drm_lease_owner(master)->lessee_idr), master->lessee_id);
	}

	/* Remove this master from any lessee list it may be on */
	list_del(&master->lessee_list);

	mutex_unlock(&dev->mode_config.idr_mutex);

	if (master->lessor) {
		/* Tell the master to check the lessee list */
		drm_sysfs_lease_event(dev);
		drm_master_put(&master->lessor);
	}

	DRM_DEBUG_LEASE("drm_lease_destroy done %d\n", master->lessee_id);
}