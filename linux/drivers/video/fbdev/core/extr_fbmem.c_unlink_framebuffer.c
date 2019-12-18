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
struct fb_info {int node; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_MAJOR ; 
 int FB_MAX ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_class ; 
 int /*<<< orphan*/  pm_vt_switch_unregister (int /*<<< orphan*/ *) ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  unbind_console (struct fb_info*) ; 

void unlink_framebuffer(struct fb_info *fb_info)
{
	int i;

	i = fb_info->node;
	if (WARN_ON(i < 0 || i >= FB_MAX || registered_fb[i] != fb_info))
		return;

	if (!fb_info->dev)
		return;

	device_destroy(fb_class, MKDEV(FB_MAJOR, i));

	pm_vt_switch_unregister(fb_info->dev);

	unbind_console(fb_info);

	fb_info->dev = NULL;
}