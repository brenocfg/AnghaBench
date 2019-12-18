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
struct rcar_pcie {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFINIT ; 
 int DL_DOWN ; 
 int /*<<< orphan*/  PCIETCTLR ; 
 int /*<<< orphan*/  PMSR ; 
 struct rcar_pcie* dev_get_drvdata (struct device*) ; 
 int rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rcar_pcie_wait_for_dl (struct rcar_pcie*) ; 

__attribute__((used)) static int rcar_pcie_resume_noirq(struct device *dev)
{
	struct rcar_pcie *pcie = dev_get_drvdata(dev);

	if (rcar_pci_read_reg(pcie, PMSR) &&
	    !(rcar_pci_read_reg(pcie, PCIETCTLR) & DL_DOWN))
		return 0;

	/* Re-establish the PCIe link */
	rcar_pci_write_reg(pcie, CFINIT, PCIETCTLR);
	return rcar_pcie_wait_for_dl(pcie);
}