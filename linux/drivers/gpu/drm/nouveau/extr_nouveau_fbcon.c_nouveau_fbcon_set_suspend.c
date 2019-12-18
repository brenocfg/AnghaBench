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
struct nouveau_drm {int fbcon_new_state; int /*<<< orphan*/  fbcon_work; int /*<<< orphan*/  fbcon; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void
nouveau_fbcon_set_suspend(struct drm_device *dev, int state)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (!drm->fbcon)
		return;

	drm->fbcon_new_state = state;
	/* Since runtime resume can happen as a result of a sysfs operation,
	 * it's possible we already have the console locked. So handle fbcon
	 * init/deinit from a seperate work thread
	 */
	schedule_work(&drm->fbcon_work);
}