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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct brcmf_pciedev_info {int /*<<< orphan*/  ci; struct pci_dev* pdev; } ;
struct brcmf_core {scalar_t__ base; } ;
struct brcmf_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_PCIE_BAR0_WINDOW ; 
 struct brcmf_core* brcmf_chip_get_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*,int /*<<< orphan*/ ) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_read_config_dword (struct pci_dev const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
brcmf_pcie_select_core(struct brcmf_pciedev_info *devinfo, u16 coreid)
{
	const struct pci_dev *pdev = devinfo->pdev;
	struct brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	struct brcmf_core *core;
	u32 bar0_win;

	core = brcmf_chip_get_core(devinfo->ci, coreid);
	if (core) {
		bar0_win = core->base;
		pci_write_config_dword(pdev, BRCMF_PCIE_BAR0_WINDOW, bar0_win);
		if (pci_read_config_dword(pdev, BRCMF_PCIE_BAR0_WINDOW,
					  &bar0_win) == 0) {
			if (bar0_win != core->base) {
				bar0_win = core->base;
				pci_write_config_dword(pdev,
						       BRCMF_PCIE_BAR0_WINDOW,
						       bar0_win);
			}
		}
	} else {
		brcmf_err(bus, "Unsupported core selected %x\n", coreid);
	}
}