#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  smem_len; } ;
struct TYPE_4__ {TYPE_1__ fix; int /*<<< orphan*/  cmap; } ;
struct ocfb_dev {int /*<<< orphan*/  fb_phys; int /*<<< orphan*/  fb_virt; TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFB_CTRL ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfb_writereg (struct ocfb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ocfb_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_2__*) ; 

__attribute__((used)) static int ocfb_remove(struct platform_device *pdev)
{
	struct ocfb_dev *fbdev = platform_get_drvdata(pdev);

	unregister_framebuffer(&fbdev->info);
	fb_dealloc_cmap(&fbdev->info.cmap);
	dma_free_coherent(&pdev->dev, PAGE_ALIGN(fbdev->info.fix.smem_len),
			  fbdev->fb_virt, fbdev->fb_phys);

	/* Disable display */
	ocfb_writereg(fbdev, OCFB_CTRL, 0);

	platform_set_drvdata(pdev, NULL);

	return 0;
}