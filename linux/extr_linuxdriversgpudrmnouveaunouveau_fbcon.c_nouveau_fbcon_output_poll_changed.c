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
struct nouveau_fbdev {int hotplug_waiting; int /*<<< orphan*/  hotplug_lock; int /*<<< orphan*/  helper; } ;
struct nouveau_drm {TYPE_1__* dev; struct nouveau_fbdev* fbcon; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*,int) ; 
 int EACCES ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

void
nouveau_fbcon_output_poll_changed(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_fbdev *fbcon = drm->fbcon;
	int ret;

	if (!fbcon)
		return;

	mutex_lock(&fbcon->hotplug_lock);

	ret = pm_runtime_get(dev->dev);
	if (ret == 1 || ret == -EACCES) {
		drm_fb_helper_hotplug_event(&fbcon->helper);

		pm_runtime_mark_last_busy(dev->dev);
		pm_runtime_put_autosuspend(dev->dev);
	} else if (ret == 0) {
		/* If the GPU was already in the process of suspending before
		 * this event happened, then we can't block here as we'll
		 * deadlock the runtime pmops since they wait for us to
		 * finish. So, just defer this event for when we runtime
		 * resume again. It will be handled by fbcon_work.
		 */
		NV_DEBUG(drm, "fbcon HPD event deferred until runtime resume\n");
		fbcon->hotplug_waiting = true;
		pm_runtime_put_noidle(drm->dev->dev);
	} else {
		DRM_WARN("fbcon HPD event lost due to RPM failure: %d\n",
			 ret);
	}

	mutex_unlock(&fbcon->hotplug_lock);
}