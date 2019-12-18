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
struct savagefb_par {int pm_state; } ;
struct pci_dev {int dummy; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int PM_EVENT_FREEZE ; 
 int PM_EVENT_ON ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fb_set_suspend (struct fb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savage_enable_mmio (struct savagefb_par*) ; 
 int /*<<< orphan*/  savage_init_hw (struct savagefb_par*) ; 
 int /*<<< orphan*/  savagefb_blank (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  savagefb_set_par (struct fb_info*) ; 

__attribute__((used)) static int savagefb_resume(struct pci_dev* dev)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct savagefb_par *par = info->par;
	int cur_state = par->pm_state;

	DBG("savage_resume");

	par->pm_state = PM_EVENT_ON;

	/*
	 * The adapter was not powered down coming back from a
	 * PM_EVENT_FREEZE.
	 */
	if (cur_state == PM_EVENT_FREEZE) {
		pci_set_power_state(dev, PCI_D0);
		return 0;
	}

	console_lock();

	pci_set_power_state(dev, PCI_D0);
	pci_restore_state(dev);

	if (pci_enable_device(dev))
		DBG("err");

	pci_set_master(dev);
	savage_enable_mmio(par);
	savage_init_hw(par);
	savagefb_set_par(info);
	fb_set_suspend(info, 0);
	savagefb_blank(FB_BLANK_UNBLANK, info);
	console_unlock();

	return 0;
}