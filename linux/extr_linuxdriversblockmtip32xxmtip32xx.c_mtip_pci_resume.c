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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct driver_data {int /*<<< orphan*/  dd_flag; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MTIP_DDF_RESUME_BIT ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mtip_block_resume (struct driver_data*) ; 
 struct driver_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pcim_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int mtip_pci_resume(struct pci_dev *pdev)
{
	int rv = 0;
	struct driver_data *dd;

	dd = pci_get_drvdata(pdev);
	if (!dd) {
		dev_err(&pdev->dev,
			"Driver private datastructure is NULL\n");
		return -EFAULT;
	}

	/* Move the device to active State */
	pci_set_power_state(pdev, PCI_D0);

	/* Restore PCI configuration space */
	pci_restore_state(pdev);

	/* Enable the PCI device*/
	rv = pcim_enable_device(pdev);
	if (rv < 0) {
		dev_err(&pdev->dev,
			"Failed to enable card during resume\n");
		goto err;
	}
	pci_set_master(pdev);

	/*
	 * Calls hbaReset, initPort, & startPort function
	 * then enables interrupts
	 */
	rv = mtip_block_resume(dd);
	if (rv < 0)
		dev_err(&pdev->dev, "Unable to resume\n");

err:
	clear_bit(MTIP_DDF_RESUME_BIT, &dd->dd_flag);

	return rv;
}