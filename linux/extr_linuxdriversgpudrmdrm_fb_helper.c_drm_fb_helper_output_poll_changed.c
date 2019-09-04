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
struct drm_device {int /*<<< orphan*/  fb_helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_hotplug_event (int /*<<< orphan*/ ) ; 

void drm_fb_helper_output_poll_changed(struct drm_device *dev)
{
	drm_fb_helper_hotplug_event(dev->fb_helper);
}