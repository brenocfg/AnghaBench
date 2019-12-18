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
struct pci_dev {int aer_cap; } ;
struct aer_err_info {scalar_t__ severity; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ AER_CORRECTABLE ; 
 scalar_t__ AER_FATAL ; 
 scalar_t__ AER_NONFATAL ; 
 int /*<<< orphan*/  PCIE_PORT_SERVICE_AER ; 
 scalar_t__ PCI_ERR_COR_STATUS ; 
 int /*<<< orphan*/  pci_aer_clear_device_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_channel_io_frozen ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_do_recovery (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_error_source(struct pci_dev *dev, struct aer_err_info *info)
{
	int pos;

	if (info->severity == AER_CORRECTABLE) {
		/*
		 * Correctable error does not need software intervention.
		 * No need to go through error recovery process.
		 */
		pos = dev->aer_cap;
		if (pos)
			pci_write_config_dword(dev, pos + PCI_ERR_COR_STATUS,
					info->status);
		pci_aer_clear_device_status(dev);
	} else if (info->severity == AER_NONFATAL)
		pcie_do_recovery(dev, pci_channel_io_normal,
				 PCIE_PORT_SERVICE_AER);
	else if (info->severity == AER_FATAL)
		pcie_do_recovery(dev, pci_channel_io_frozen,
				 PCIE_PORT_SERVICE_AER);
	pci_dev_put(dev);
}