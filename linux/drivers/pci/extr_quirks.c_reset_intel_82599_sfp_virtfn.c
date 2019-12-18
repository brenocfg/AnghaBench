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

/* Variables and functions */
 int /*<<< orphan*/  pcie_flr (struct pci_dev*) ; 

__attribute__((used)) static int reset_intel_82599_sfp_virtfn(struct pci_dev *dev, int probe)
{
	/*
	 * http://www.intel.com/content/dam/doc/datasheet/82599-10-gbe-controller-datasheet.pdf
	 *
	 * The 82599 supports FLR on VFs, but FLR support is reported only
	 * in the PF DEVCAP (sec 9.3.10.4), not in the VF DEVCAP (sec 9.5).
	 * Thus we must call pcie_flr() directly without first checking if it is
	 * supported.
	 */
	if (!probe)
		pcie_flr(dev);
	return 0;
}