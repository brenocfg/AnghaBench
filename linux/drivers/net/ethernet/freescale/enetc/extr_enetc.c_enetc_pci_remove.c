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
struct enetc_hw {int /*<<< orphan*/  reg; } ;
struct enetc_si {struct enetc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_kfree_si (struct enetc_si*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct enetc_si* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 

void enetc_pci_remove(struct pci_dev *pdev)
{
	struct enetc_si *si = pci_get_drvdata(pdev);
	struct enetc_hw *hw = &si->hw;

	iounmap(hw->reg);
	enetc_kfree_si(si);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}