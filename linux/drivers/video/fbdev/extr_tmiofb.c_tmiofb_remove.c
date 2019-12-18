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
struct tmiofb_par {int /*<<< orphan*/  ccr; int /*<<< orphan*/  lcr; } ;
struct platform_device {int dummy; } ;
struct mfd_cell {int /*<<< orphan*/  (* disable ) (struct platform_device*) ;} ;
struct fb_info {int /*<<< orphan*/  screen_base; struct tmiofb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  free_irq (int,struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct mfd_cell* mfd_get_cell (struct platform_device*) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  tmiofb_hw_stop (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int tmiofb_remove(struct platform_device *dev)
{
	const struct mfd_cell *cell = mfd_get_cell(dev);
	struct fb_info *info = platform_get_drvdata(dev);
	int irq = platform_get_irq(dev, 0);
	struct tmiofb_par *par;

	if (info) {
		par = info->par;
		unregister_framebuffer(info);

		tmiofb_hw_stop(dev);

		if (cell->disable)
			cell->disable(dev);

		free_irq(irq, info);

		iounmap(info->screen_base);
		iounmap(par->lcr);
		iounmap(par->ccr);

		framebuffer_release(info);
	}

	return 0;
}