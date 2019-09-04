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
struct TYPE_4__ {scalar_t__ deferred_setup; } ;
struct intel_fbdev {int hpd_waiting; TYPE_2__ helper; scalar_t__ vma; int /*<<< orphan*/  hpd_lock; int /*<<< orphan*/  hpd_suspended; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct intel_fbdev* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_fbdev_sync (struct intel_fbdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_i915 (struct drm_device*) ; 

void intel_fbdev_output_poll_changed(struct drm_device *dev)
{
	struct intel_fbdev *ifbdev = to_i915(dev)->fbdev;
	bool send_hpd;

	if (!ifbdev)
		return;

	intel_fbdev_sync(ifbdev);

	mutex_lock(&ifbdev->hpd_lock);
	send_hpd = !ifbdev->hpd_suspended;
	ifbdev->hpd_waiting = true;
	mutex_unlock(&ifbdev->hpd_lock);

	if (send_hpd && (ifbdev->vma || ifbdev->helper.deferred_setup))
		drm_fb_helper_hotplug_event(&ifbdev->helper);
}