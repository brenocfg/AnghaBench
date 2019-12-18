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
struct brcmf_pciedev_info {int /*<<< orphan*/  pdev; scalar_t__ regs; scalar_t__ tcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_pcie_release_resource(struct brcmf_pciedev_info *devinfo)
{
	if (devinfo->tcm)
		iounmap(devinfo->tcm);
	if (devinfo->regs)
		iounmap(devinfo->regs);

	pci_disable_device(devinfo->pdev);
}