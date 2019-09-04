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
struct drm_file {TYPE_1__* master; int /*<<< orphan*/  is_master; } ;
struct drm_device {int /*<<< orphan*/  master_mutex; scalar_t__ master; } ;
struct TYPE_2__ {int /*<<< orphan*/  lessee_id; int /*<<< orphan*/ * lessor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_LEASE (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ drm_is_current_master (struct drm_file*) ; 
 int drm_new_set_master (struct drm_device*,struct drm_file*) ; 
 int drm_set_master (struct drm_device*,struct drm_file*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_setmaster_ioctl(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	int ret = 0;

	mutex_lock(&dev->master_mutex);
	if (drm_is_current_master(file_priv))
		goto out_unlock;

	if (dev->master) {
		ret = -EINVAL;
		goto out_unlock;
	}

	if (!file_priv->master) {
		ret = -EINVAL;
		goto out_unlock;
	}

	if (!file_priv->is_master) {
		ret = drm_new_set_master(dev, file_priv);
		goto out_unlock;
	}

	if (file_priv->master->lessor != NULL) {
		DRM_DEBUG_LEASE("Attempt to set lessee %d as master\n", file_priv->master->lessee_id);
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = drm_set_master(dev, file_priv, false);
out_unlock:
	mutex_unlock(&dev->master_mutex);
	return ret;
}