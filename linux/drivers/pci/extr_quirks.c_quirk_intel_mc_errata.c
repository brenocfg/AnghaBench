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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE_BUS_DEFAULT ; 
 scalar_t__ PCIE_BUS_TUNE_OFF ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*) ; 
 int pci_read_config_word (struct pci_dev*,int,int*) ; 
 int pci_write_config_word (struct pci_dev*,int,int) ; 
 scalar_t__ pcie_bus_config ; 
 int /*<<< orphan*/  pr_info_once (char*) ; 

__attribute__((used)) static void quirk_intel_mc_errata(struct pci_dev *dev)
{
	int err;
	u16 rcc;

	if (pcie_bus_config == PCIE_BUS_TUNE_OFF ||
	    pcie_bus_config == PCIE_BUS_DEFAULT)
		return;

	/*
	 * Intel erratum specifies bits to change but does not say what
	 * they are.  Keeping them magical until such time as the registers
	 * and values can be explained.
	 */
	err = pci_read_config_word(dev, 0x48, &rcc);
	if (err) {
		pci_err(dev, "Error attempting to read the read completion coalescing register\n");
		return;
	}

	if (!(rcc & (1 << 10)))
		return;

	rcc &= ~(1 << 10);

	err = pci_write_config_word(dev, 0x48, rcc);
	if (err) {
		pci_err(dev, "Error attempting to write the read completion coalescing register\n");
		return;
	}

	pr_info_once("Read completion coalescing disabled due to hardware erratum relating to 256B MPS\n");
}