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
struct drm_mode_revoke_lease {int /*<<< orphan*/  lessee_id; } ;
struct drm_master {struct drm_master* lessor; } ;
struct drm_file {struct drm_master* master; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_LEASE (char*,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 struct drm_master* _drm_find_lessee (struct drm_master*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drm_lease_revoke (struct drm_master*) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_mode_revoke_lease_ioctl(struct drm_device *dev,
				void *data, struct drm_file *lessor_priv)
{
	struct drm_mode_revoke_lease *arg = data;
	struct drm_master *lessor = lessor_priv->master;
	struct drm_master *lessee;
	int ret = 0;

	DRM_DEBUG_LEASE("revoke lease for %d\n", arg->lessee_id);

	/* Can't lease without MODESET */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	mutex_lock(&dev->mode_config.idr_mutex);

	lessee = _drm_find_lessee(lessor, arg->lessee_id);

	/* No such lessee */
	if (!lessee) {
		ret = -ENOENT;
		goto fail;
	}

	/* Lease is not held by lessor */
	if (lessee->lessor != lessor) {
		ret = -EACCES;
		goto fail;
	}

	_drm_lease_revoke(lessee);

fail:
	mutex_unlock(&dev->mode_config.idr_mutex);

	return ret;
}