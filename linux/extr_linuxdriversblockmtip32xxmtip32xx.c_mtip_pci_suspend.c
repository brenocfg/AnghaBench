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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  MTIP_DDF_RESUME_BIT ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mtip_block_suspend (struct driver_data*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct driver_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_pci_suspend(struct pci_dev *pdev, pm_message_t mesg)
{
	int rv = 0;
	struct driver_data *dd = pci_get_drvdata(pdev);

	if (!dd) {
		dev_err(&pdev->dev,
			"Driver private datastructure is NULL\n");
		return -EFAULT;
	}

	set_bit(MTIP_DDF_RESUME_BIT, &dd->dd_flag);

	/* Disable ports & interrupts then send standby immediate */
	rv = mtip_block_suspend(dd);
	if (rv < 0) {
		dev_err(&pdev->dev,
			"Failed to suspend controller\n");
		return rv;
	}

	/*
	 * Save the pci config space to pdev structure &
	 * disable the device
	 */
	pci_save_state(pdev);
	pci_disable_device(pdev);

	/* Move to Low power state*/
	pci_set_power_state(pdev, PCI_D3hot);

	return rv;
}