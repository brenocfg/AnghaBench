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

/* Variables and functions */
 int /*<<< orphan*/  knl_pci_uncores ; 
 int /*<<< orphan*/  knl_uncore_pci_driver ; 
 int snb_pci2phy_map_init (int) ; 
 int /*<<< orphan*/ * uncore_pci_driver ; 
 int /*<<< orphan*/  uncore_pci_uncores ; 

int knl_uncore_pci_init(void)
{
	int ret;

	/* All KNL PCI based PMON units are on the same PCI bus except IRP */
	ret = snb_pci2phy_map_init(0x7814); /* IRP */
	if (ret)
		return ret;
	ret = snb_pci2phy_map_init(0x7817); /* M2PCIe */
	if (ret)
		return ret;
	uncore_pci_uncores = knl_pci_uncores;
	uncore_pci_driver = &knl_uncore_pci_driver;
	return 0;
}