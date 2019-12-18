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
struct sh_mobile_lcdc_overlay {struct fb_info* info; } ;
struct fb_info {int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 

__attribute__((used)) static void
sh_mobile_lcdc_overlay_fb_cleanup(struct sh_mobile_lcdc_overlay *ovl)
{
	struct fb_info *info = ovl->info;

	if (info == NULL || info->device == NULL)
		return;

	framebuffer_release(info);
}