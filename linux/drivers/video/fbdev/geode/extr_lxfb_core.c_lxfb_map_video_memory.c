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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lxfb_par {int /*<<< orphan*/ * vp_regs; int /*<<< orphan*/ * dc_regs; int /*<<< orphan*/ * gp_regs; } ;
struct TYPE_2__ {int smem_start; int smem_len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/ * screen_base; struct lxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_GLIU0_MEM_OFFSET ; 
 int /*<<< orphan*/  DC_UNLOCK ; 
 int DC_UNLOCK_LOCK ; 
 int DC_UNLOCK_UNLOCK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/ * ioremap (int,int) ; 
 int lx_framebuffer_size () ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_ioremap_bar (struct pci_dev*,int) ; 
 int pci_request_region (struct pci_dev*,int,char*) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int vram ; 
 int /*<<< orphan*/  write_dc (struct lxfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lxfb_map_video_memory(struct fb_info *info, struct pci_dev *dev)
{
	struct lxfb_par *par = info->par;
	int ret;

	ret = pci_enable_device(dev);

	if (ret)
		return ret;

	ret = pci_request_region(dev, 0, "lxfb-framebuffer");

	if (ret)
		return ret;

	ret = pci_request_region(dev, 1, "lxfb-gp");

	if (ret)
		return ret;

	ret = pci_request_region(dev, 2, "lxfb-vg");

	if (ret)
		return ret;

	ret = pci_request_region(dev, 3, "lxfb-vp");

	if (ret)
		return ret;

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = vram ? vram : lx_framebuffer_size();

	info->screen_base = ioremap(info->fix.smem_start, info->fix.smem_len);

	ret = -ENOMEM;

	if (info->screen_base == NULL)
		return ret;

	par->gp_regs = pci_ioremap_bar(dev, 1);

	if (par->gp_regs == NULL)
		return ret;

	par->dc_regs = pci_ioremap_bar(dev, 2);

	if (par->dc_regs == NULL)
		return ret;

	par->vp_regs = pci_ioremap_bar(dev, 3);

	if (par->vp_regs == NULL)
		return ret;

	write_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
	write_dc(par, DC_GLIU0_MEM_OFFSET, info->fix.smem_start & 0xFF000000);
	write_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);

	dev_info(&dev->dev, "%d KB of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	return 0;
}