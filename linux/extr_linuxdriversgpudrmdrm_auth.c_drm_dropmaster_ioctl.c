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
struct drm_file {TYPE_1__* master; } ;
struct drm_device {int /*<<< orphan*/  master_mutex; int /*<<< orphan*/  master; } ;
struct TYPE_2__ {int /*<<< orphan*/  lessee_id; int /*<<< orphan*/ * lessor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_LEASE (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_drop_master (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_is_current_master (struct drm_file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_dropmaster_ioctl(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	int ret = -EINVAL;

	mutex_lock(&dev->master_mutex);
	if (!drm_is_current_master(file_priv))
		goto out_unlock;

	if (!dev->master)
		goto out_unlock;

	if (file_priv->master->lessor != NULL) {
		DRM_DEBUG_LEASE("Attempt to drop lessee %d as master\n", file_priv->master->lessee_id);
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = 0;
	drm_drop_master(dev, file_priv);
out_unlock:
	mutex_unlock(&dev->master_mutex);
	return ret;
}