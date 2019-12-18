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
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int devfn; int aer_cap; int /*<<< orphan*/  enable_cnt; TYPE_1__* bus; } ;
struct aer_err_info {int id; scalar_t__ severity; int /*<<< orphan*/  multi_error_valid; } ;
struct TYPE_2__ {int bus_flags; int number; } ;

/* Variables and functions */
 scalar_t__ AER_CORRECTABLE ; 
 int PCI_BUS_FLAGS_NO_AERSID ; 
 scalar_t__ PCI_BUS_NUM (int) ; 
 scalar_t__ PCI_ERR_COR_MASK ; 
 scalar_t__ PCI_ERR_COR_STATUS ; 
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_STATUS ; 
 int PCI_EXP_AER_FLAGS ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool is_error_source(struct pci_dev *dev, struct aer_err_info *e_info)
{
	int pos;
	u32 status, mask;
	u16 reg16;

	/*
	 * When bus id is equal to 0, it might be a bad id
	 * reported by root port.
	 */
	if ((PCI_BUS_NUM(e_info->id) != 0) &&
	    !(dev->bus->bus_flags & PCI_BUS_FLAGS_NO_AERSID)) {
		/* Device ID match? */
		if (e_info->id == ((dev->bus->number << 8) | dev->devfn))
			return true;

		/* Continue id comparing if there is no multiple error */
		if (!e_info->multi_error_valid)
			return false;
	}

	/*
	 * When either
	 *      1) bus id is equal to 0. Some ports might lose the bus
	 *              id of error source id;
	 *      2) bus flag PCI_BUS_FLAGS_NO_AERSID is set
	 *      3) There are multiple errors and prior ID comparing fails;
	 * We check AER status registers to find possible reporter.
	 */
	if (atomic_read(&dev->enable_cnt) == 0)
		return false;

	/* Check if AER is enabled */
	pcie_capability_read_word(dev, PCI_EXP_DEVCTL, &reg16);
	if (!(reg16 & PCI_EXP_AER_FLAGS))
		return false;

	pos = dev->aer_cap;
	if (!pos)
		return false;

	/* Check if error is recorded */
	if (e_info->severity == AER_CORRECTABLE) {
		pci_read_config_dword(dev, pos + PCI_ERR_COR_STATUS, &status);
		pci_read_config_dword(dev, pos + PCI_ERR_COR_MASK, &mask);
	} else {
		pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, &status);
		pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, &mask);
	}
	if (status & ~mask)
		return true;

	return false;
}