#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s1d13xxxfb_par {scalar_t__ regs; } ;
struct platform_device {TYPE_1__* resource; } ;
struct fb_info {scalar_t__ screen_base; int /*<<< orphan*/  cmap; struct s1d13xxxfb_par* par; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  S1DREG_COM_DISP_MODE ; 
 int /*<<< orphan*/  S1DREG_PS_CNF ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  s1d13xxxfb_writereg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
s1d13xxxfb_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);
	struct s1d13xxxfb_par *par = NULL;

	if (info) {
		par = info->par;
		if (par && par->regs) {
			/* disable output & enable powersave */
			s1d13xxxfb_writereg(par, S1DREG_COM_DISP_MODE, 0x00);
			s1d13xxxfb_writereg(par, S1DREG_PS_CNF, 0x11);
			iounmap(par->regs);
		}

		fb_dealloc_cmap(&info->cmap);

		if (info->screen_base)
			iounmap(info->screen_base);

		framebuffer_release(info);
	}

	release_mem_region(pdev->resource[0].start,
			pdev->resource[0].end - pdev->resource[0].start +1);
	release_mem_region(pdev->resource[1].start,
			pdev->resource[1].end - pdev->resource[1].start +1);
	return 0;
}