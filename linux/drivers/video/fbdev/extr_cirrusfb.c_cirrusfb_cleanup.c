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
struct fb_info {int /*<<< orphan*/  device; int /*<<< orphan*/  cmap; struct cirrusfb_info* par; } ;
struct cirrusfb_info {int /*<<< orphan*/  (* unmap ) (struct fb_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  switch_monitor (struct cirrusfb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void cirrusfb_cleanup(struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;

	switch_monitor(cinfo, 0);
	unregister_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	dev_dbg(info->device, "Framebuffer unregistered\n");
	cinfo->unmap(info);
	framebuffer_release(info);
}