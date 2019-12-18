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
struct TYPE_2__ {int /*<<< orphan*/  modedb; } ;
struct fb_info {TYPE_1__ monspecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  fb_destroy_modedb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neo_free_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  neo_unmap_mmio (struct fb_info*) ; 
 int /*<<< orphan*/  neo_unmap_video (struct fb_info*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void neofb_remove(struct pci_dev *dev)
{
	struct fb_info *info = pci_get_drvdata(dev);

	DBG("neofb_remove");

	if (info) {
		unregister_framebuffer(info);

		neo_unmap_video(info);
		fb_destroy_modedb(info->monspecs.modedb);
		neo_unmap_mmio(info);
		neo_free_fb_info(info);
	}
}