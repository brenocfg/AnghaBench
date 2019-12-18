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
typedef  int u32 ;
struct resource {int dummy; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXT_CAP_ID_REBAR ; 
 scalar_t__ PCI_REBAR_CTRL ; 
 int PCI_REBAR_CTRL_BAR_IDX ; 
 int PCI_REBAR_CTRL_BAR_SHIFT ; 
 int PCI_REBAR_CTRL_BAR_SIZE ; 
 int PCI_REBAR_CTRL_NBAR_MASK ; 
 int PCI_REBAR_CTRL_NBAR_SHIFT ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 unsigned int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static void pci_restore_rebar_state(struct pci_dev *pdev)
{
	unsigned int pos, nbars, i;
	u32 ctrl;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_REBAR);
	if (!pos)
		return;

	pci_read_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
	nbars = (ctrl & PCI_REBAR_CTRL_NBAR_MASK) >>
		    PCI_REBAR_CTRL_NBAR_SHIFT;

	for (i = 0; i < nbars; i++, pos += 8) {
		struct resource *res;
		int bar_idx, size;

		pci_read_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
		bar_idx = ctrl & PCI_REBAR_CTRL_BAR_IDX;
		res = pdev->resource + bar_idx;
		size = ilog2(resource_size(res)) - 20;
		ctrl &= ~PCI_REBAR_CTRL_BAR_SIZE;
		ctrl |= size << PCI_REBAR_CTRL_BAR_SHIFT;
		pci_write_config_dword(pdev, pos + PCI_REBAR_CTRL, ctrl);
	}
}