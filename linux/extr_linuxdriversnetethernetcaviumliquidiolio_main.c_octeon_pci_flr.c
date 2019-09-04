#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {TYPE_1__* pci_dev; int /*<<< orphan*/  pf_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_INTX_DISABLE ; 
 int __pci_reset_function_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_access_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_restore_state (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_save_state (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_pci_flr(struct octeon_device *oct)
{
	int rc;

	pci_save_state(oct->pci_dev);

	pci_cfg_access_lock(oct->pci_dev);

	/* Quiesce the device completely */
	pci_write_config_word(oct->pci_dev, PCI_COMMAND,
			      PCI_COMMAND_INTX_DISABLE);

	rc = __pci_reset_function_locked(oct->pci_dev);

	if (rc != 0)
		dev_err(&oct->pci_dev->dev, "Error %d resetting PCI function %d\n",
			rc, oct->pf_num);

	pci_cfg_access_unlock(oct->pci_dev);

	pci_restore_state(oct->pci_dev);
}