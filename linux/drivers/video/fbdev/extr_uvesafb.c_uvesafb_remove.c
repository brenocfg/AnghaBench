#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uvesafb_par {int /*<<< orphan*/  vbe_state_saved; int /*<<< orphan*/  vbe_state_orig; int /*<<< orphan*/  vbe_modes; int /*<<< orphan*/  mtrr_handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  modedb; } ;
struct TYPE_5__ {int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {int /*<<< orphan*/  cmap; TYPE_3__ monspecs; TYPE_2__ fix; int /*<<< orphan*/  screen_base; struct uvesafb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_destroy_modedb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  uvesafb_dev_attgrp ; 

__attribute__((used)) static int uvesafb_remove(struct platform_device *dev)
{
	struct fb_info *info = platform_get_drvdata(dev);

	if (info) {
		struct uvesafb_par *par = info->par;

		sysfs_remove_group(&dev->dev.kobj, &uvesafb_dev_attgrp);
		unregister_framebuffer(info);
		release_region(0x3c0, 32);
		iounmap(info->screen_base);
		arch_phys_wc_del(par->mtrr_handle);
		release_mem_region(info->fix.smem_start, info->fix.smem_len);
		fb_destroy_modedb(info->monspecs.modedb);
		fb_dealloc_cmap(&info->cmap);

		kfree(par->vbe_modes);
		kfree(par->vbe_state_orig);
		kfree(par->vbe_state_saved);

		framebuffer_release(info);
	}
	return 0;
}