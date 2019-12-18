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
struct kyrofb_info {int /*<<< orphan*/  wc_cookie; int /*<<< orphan*/  regbase; } ;
struct fb_info {int /*<<< orphan*/  screen_base; struct kyrofb_info* par; } ;
struct TYPE_2__ {scalar_t__ ulOverlayOffset; scalar_t__ ulNextFreeVidMem; int /*<<< orphan*/  pSTGReg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DisableRamdacOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCoreClockPLL (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  StopVTG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 TYPE_1__ deviceInfo ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void kyrofb_remove(struct pci_dev *pdev)
{
	struct fb_info *info = pci_get_drvdata(pdev);
	struct kyrofb_info *par = info->par;

	/* Reset the board */
	StopVTG(deviceInfo.pSTGReg);
	DisableRamdacOutput(deviceInfo.pSTGReg);

	/* Sync up the PLL */
	SetCoreClockPLL(deviceInfo.pSTGReg, pdev);

	deviceInfo.ulNextFreeVidMem = 0;
	deviceInfo.ulOverlayOffset = 0;

	iounmap(info->screen_base);
	iounmap(par->regbase);

	arch_phys_wc_del(par->wc_cookie);

	unregister_framebuffer(info);
	framebuffer_release(info);
}