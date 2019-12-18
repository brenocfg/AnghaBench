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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct nouveau_fbdev {int hotplug_waiting; int /*<<< orphan*/  hotplug_lock; TYPE_1__ helper; } ;
struct nouveau_drm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

void
nouveau_fbcon_hotplug_resume(struct nouveau_fbdev *fbcon)
{
	struct nouveau_drm *drm;

	if (!fbcon)
		return;
	drm = nouveau_drm(fbcon->helper.dev);

	mutex_lock(&fbcon->hotplug_lock);
	if (fbcon->hotplug_waiting) {
		fbcon->hotplug_waiting = false;

		NV_DEBUG(drm, "Handling deferred fbcon HPD events\n");
		drm_fb_helper_hotplug_event(&fbcon->helper);
	}
	mutex_unlock(&fbcon->hotplug_lock);
}