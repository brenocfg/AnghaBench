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

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_lastclose (struct drm_device*) ; 
 int /*<<< orphan*/  vga_switcheroo_process_delayed_switch () ; 

void amdgpu_driver_lastclose_kms(struct drm_device *dev)
{
	drm_fb_helper_lastclose(dev);
	vga_switcheroo_process_delayed_switch();
}