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
struct sgi_gbe {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gbefb_par {int /*<<< orphan*/  wc_cookie; } ;
struct fb_info {struct gbefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBE_BASE ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  gbe_turn_off () ; 
 int /*<<< orphan*/  gbefb_remove_sysfs (int /*<<< orphan*/ *) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int gbefb_remove(struct platform_device* p_dev)
{
	struct fb_info *info = platform_get_drvdata(p_dev);
	struct gbefb_par *par = info->par;

	unregister_framebuffer(info);
	gbe_turn_off();
	arch_phys_wc_del(par->wc_cookie);
	release_mem_region(GBE_BASE, sizeof(struct sgi_gbe));
	gbefb_remove_sysfs(&p_dev->dev);
	framebuffer_release(info);

	return 0;
}