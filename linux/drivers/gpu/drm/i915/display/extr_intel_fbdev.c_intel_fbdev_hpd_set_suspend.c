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
struct intel_fbdev {int hpd_suspended; int hpd_waiting; int /*<<< orphan*/  helper; int /*<<< orphan*/  hpd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int FBINFO_STATE_SUSPENDED ; 
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_fbdev_hpd_set_suspend(struct intel_fbdev *ifbdev, int state)
{
	bool send_hpd = false;

	mutex_lock(&ifbdev->hpd_lock);
	ifbdev->hpd_suspended = state == FBINFO_STATE_SUSPENDED;
	send_hpd = !ifbdev->hpd_suspended && ifbdev->hpd_waiting;
	ifbdev->hpd_waiting = false;
	mutex_unlock(&ifbdev->hpd_lock);

	if (send_hpd) {
		DRM_DEBUG_KMS("Handling delayed fbcon HPD event\n");
		drm_fb_helper_hotplug_event(&ifbdev->helper);
	}
}