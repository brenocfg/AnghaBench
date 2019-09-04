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
struct octeon_device {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  pci_cfg_access_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_flr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_pci_flr(struct octeon_device *oct)
{
	pci_save_state(oct->pci_dev);

	pci_cfg_access_lock(oct->pci_dev);

	/* Quiesce the device completely */
	pci_write_config_word(oct->pci_dev, PCI_COMMAND,
			      PCI_COMMAND_INTX_DISABLE);

	pcie_flr(oct->pci_dev);

	pci_cfg_access_unlock(oct->pci_dev);

	pci_restore_state(oct->pci_dev);
}