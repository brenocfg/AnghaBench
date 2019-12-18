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
struct drm_device {int dummy; } ;
struct drm_client_dev {int /*<<< orphan*/  modeset_mutex; struct drm_device* dev; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int EBUSY ; 
 int drm_client_modeset_commit_atomic (struct drm_client_dev*,int) ; 
 int /*<<< orphan*/  drm_client_modeset_dpms_legacy (struct drm_client_dev*,int) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_acquire (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_release (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_client_modeset_dpms(struct drm_client_dev *client, int mode)
{
	struct drm_device *dev = client->dev;
	int ret = 0;

	if (!drm_master_internal_acquire(dev))
		return -EBUSY;

	mutex_lock(&client->modeset_mutex);
	if (drm_drv_uses_atomic_modeset(dev))
		ret = drm_client_modeset_commit_atomic(client, mode == DRM_MODE_DPMS_ON);
	else
		drm_client_modeset_dpms_legacy(client, mode);
	mutex_unlock(&client->modeset_mutex);

	drm_master_internal_release(dev);

	return ret;
}