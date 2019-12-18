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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct imxfb_info {int /*<<< orphan*/  regs; int /*<<< orphan*/  map_dma; int /*<<< orphan*/  map_size; int /*<<< orphan*/  pdev; } ;
struct imx_fb_platform_data {int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ ) ;} ;
struct fb_info {int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  screen_buffer; int /*<<< orphan*/  cmap; struct imxfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct imx_fb_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  imxfb_disable_controller (struct imxfb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int imxfb_remove(struct platform_device *pdev)
{
	struct imx_fb_platform_data *pdata;
	struct fb_info *info = platform_get_drvdata(pdev);
	struct imxfb_info *fbi = info->par;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	imxfb_disable_controller(fbi);

	unregister_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	pdata = dev_get_platdata(&pdev->dev);
	if (pdata && pdata->exit)
		pdata->exit(fbi->pdev);
	dma_free_wc(&pdev->dev, fbi->map_size, info->screen_buffer,
		    fbi->map_dma);
	iounmap(fbi->regs);
	release_mem_region(res->start, resource_size(res));
	kfree(info->pseudo_palette);
	framebuffer_release(info);

	return 0;
}