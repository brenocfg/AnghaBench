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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct fb_info {TYPE_1__ pixmap; int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  savage_unmap_mmio (struct fb_info*) ; 
 int /*<<< orphan*/  savage_unmap_video (struct fb_info*) ; 
 int /*<<< orphan*/  savagefb_delete_i2c_busses (struct fb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void savagefb_remove(struct pci_dev *dev)
{
	struct fb_info *info = pci_get_drvdata(dev);

	DBG("savagefb_remove");

	if (info) {
		unregister_framebuffer(info);

#ifdef CONFIG_FB_SAVAGE_I2C
		savagefb_delete_i2c_busses(info);
#endif
		fb_alloc_cmap(&info->cmap, 0, 0);
		savage_unmap_video(info);
		savage_unmap_mmio(info);
		kfree(info->pixmap.addr);
		pci_release_regions(dev);
		framebuffer_release(info);
	}
}