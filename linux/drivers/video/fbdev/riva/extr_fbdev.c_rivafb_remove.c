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
struct TYPE_3__ {scalar_t__ Architecture; int /*<<< orphan*/  PRAMIN; } ;
struct riva_par {TYPE_1__ riva; int /*<<< orphan*/  ctrl_base; int /*<<< orphan*/  wc_cookie; int /*<<< orphan*/  EDID; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct fb_info {TYPE_2__ pixmap; int /*<<< orphan*/  screen_base; struct riva_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 scalar_t__ NV_ARCH_03 ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  riva_bl_exit (struct fb_info*) ; 
 int /*<<< orphan*/  riva_delete_i2c_busses (struct riva_par*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void rivafb_remove(struct pci_dev *pd)
{
	struct fb_info *info = pci_get_drvdata(pd);
	struct riva_par *par = info->par;
	
	NVTRACE_ENTER();

#ifdef CONFIG_FB_RIVA_I2C
	riva_delete_i2c_busses(par);
	kfree(par->EDID);
#endif

	unregister_framebuffer(info);

	riva_bl_exit(info);
	arch_phys_wc_del(par->wc_cookie);
	iounmap(par->ctrl_base);
	iounmap(info->screen_base);
	if (par->riva.Architecture == NV_ARCH_03)
		iounmap(par->riva.PRAMIN);
	pci_release_regions(pd);
	kfree(info->pixmap.addr);
	framebuffer_release(info);
	NVTRACE_LEAVE();
}