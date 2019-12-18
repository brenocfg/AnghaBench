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
struct tridentfb_par {int /*<<< orphan*/  io_virt; int /*<<< orphan*/  ddc_adapter; scalar_t__ ddc_registered; } ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct fb_info {int /*<<< orphan*/  cmap; TYPE_1__ pixmap; int /*<<< orphan*/  screen_base; struct tridentfb_par* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ tridentfb_fix ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void trident_pci_remove(struct pci_dev *dev)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct tridentfb_par *par = info->par;

	unregister_framebuffer(info);
	if (par->ddc_registered)
		i2c_del_adapter(&par->ddc_adapter);
	iounmap(par->io_virt);
	iounmap(info->screen_base);
	release_mem_region(tridentfb_fix.smem_start, tridentfb_fix.smem_len);
	release_mem_region(tridentfb_fix.mmio_start, tridentfb_fix.mmio_len);
	kfree(info->pixmap.addr);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
}