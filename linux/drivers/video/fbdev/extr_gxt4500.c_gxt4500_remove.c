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
struct pci_dev {int dummy; } ;
struct gxt4500_par {int /*<<< orphan*/  regs; int /*<<< orphan*/  wc_cookie; } ;
struct fb_info {int /*<<< orphan*/  screen_base; int /*<<< orphan*/  cmap; struct gxt4500_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void gxt4500_remove(struct pci_dev *pdev)
{
	struct fb_info *info = pci_get_drvdata(pdev);
	struct gxt4500_par *par;

	if (!info)
		return;
	par = info->par;
	unregister_framebuffer(info);
	arch_phys_wc_del(par->wc_cookie);
	fb_dealloc_cmap(&info->cmap);
	iounmap(par->regs);
	iounmap(info->screen_base);
	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	release_mem_region(pci_resource_start(pdev, 1),
			   pci_resource_len(pdev, 1));
	framebuffer_release(info);
}