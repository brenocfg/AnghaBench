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
struct pci_dev {int dummy; } ;
struct ef4_nic {TYPE_1__* type; int /*<<< orphan*/  pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* reset ) (struct ef4_nic*,int /*<<< orphan*/ ) ;int (* init ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  RESET_TYPE_ALL ; 
 int ef4_pm_thaw (struct device*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct ef4_nic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ef4_nic*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int ef4_pm_resume(struct device *dev)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	struct ef4_nic *efx = pci_get_drvdata(pci_dev);
	int rc;

	rc = pci_set_power_state(pci_dev, PCI_D0);
	if (rc)
		return rc;
	pci_restore_state(pci_dev);
	rc = pci_enable_device(pci_dev);
	if (rc)
		return rc;
	pci_set_master(efx->pci_dev);
	rc = efx->type->reset(efx, RESET_TYPE_ALL);
	if (rc)
		return rc;
	rc = efx->type->init(efx);
	if (rc)
		return rc;
	rc = ef4_pm_thaw(dev);
	return rc;
}