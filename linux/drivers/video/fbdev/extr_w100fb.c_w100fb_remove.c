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
struct w100fb_par {int /*<<< orphan*/  saved_extmem; int /*<<< orphan*/  saved_intmem; } ;
struct platform_device {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  pseudo_palette; struct w100fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  remapped_base ; 
 int /*<<< orphan*/  remapped_fbuf ; 
 int /*<<< orphan*/  remapped_regs ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w100fb_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);
	struct w100fb_par *par=info->par;

	unregister_framebuffer(info);

	vfree(par->saved_intmem);
	vfree(par->saved_extmem);
	kfree(info->pseudo_palette);
	fb_dealloc_cmap(&info->cmap);

	iounmap(remapped_base);
	iounmap(remapped_regs);
	iounmap(remapped_fbuf);

	framebuffer_release(info);

	return 0;
}