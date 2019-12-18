#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  smem_len; } ;
struct TYPE_5__ {TYPE_1__ fix; int /*<<< orphan*/  cmap; } ;
struct xilinxfb_drvdata {int flags; int /*<<< orphan*/  dcr_len; int /*<<< orphan*/  dcr_host; int /*<<< orphan*/  fb_virt; int /*<<< orphan*/  fb_phys; TYPE_2__ info; scalar_t__ fb_alloced; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BUS_ACCESS_FLAG ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  VESA_POWERDOWN ; 
 int /*<<< orphan*/  dcr_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xilinxfb_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  xilinx_fb_blank (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  xilinx_fb_out32 (struct xilinxfb_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xilinxfb_release(struct device *dev)
{
	struct xilinxfb_drvdata *drvdata = dev_get_drvdata(dev);

#if !defined(CONFIG_FRAMEBUFFER_CONSOLE) && defined(CONFIG_LOGO)
	xilinx_fb_blank(VESA_POWERDOWN, &drvdata->info);
#endif

	unregister_framebuffer(&drvdata->info);

	fb_dealloc_cmap(&drvdata->info.cmap);

	if (drvdata->fb_alloced)
		dma_free_coherent(dev, PAGE_ALIGN(drvdata->info.fix.smem_len),
				  drvdata->fb_virt, drvdata->fb_phys);
	else
		iounmap(drvdata->fb_virt);

	/* Turn off the display */
	xilinx_fb_out32(drvdata, REG_CTRL, 0);

#ifdef CONFIG_PPC_DCR
	/* Release the resources, as allocated based on interface */
	if (!(drvdata->flags & BUS_ACCESS_FLAG))
		dcr_unmap(drvdata->dcr_host, drvdata->dcr_len);
#endif

	return 0;
}