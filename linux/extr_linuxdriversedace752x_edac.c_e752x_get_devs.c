#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct e752x_pvt {int /*<<< orphan*/ * dev_d0f1; int /*<<< orphan*/ * dev_d0f0; TYPE_1__* dev_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctl_dev; int /*<<< orphan*/  err_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 TYPE_2__* e752x_devs ; 
 int /*<<< orphan*/  e752x_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ *) ; 
 void* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_scan_single_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e752x_get_devs(struct pci_dev *pdev, int dev_idx,
			struct e752x_pvt *pvt)
{
	pvt->dev_d0f1 = pci_get_device(PCI_VENDOR_ID_INTEL,
				pvt->dev_info->err_dev, NULL);

	if (pvt->dev_d0f1 == NULL) {
		pvt->dev_d0f1 = pci_scan_single_device(pdev->bus,
							PCI_DEVFN(0, 1));
		pci_dev_get(pvt->dev_d0f1);
	}

	if (pvt->dev_d0f1 == NULL) {
		e752x_printk(KERN_ERR, "error reporting device not found:"
			"vendor %x device 0x%x (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, e752x_devs[dev_idx].err_dev);
		return 1;
	}

	pvt->dev_d0f0 = pci_get_device(PCI_VENDOR_ID_INTEL,
				e752x_devs[dev_idx].ctl_dev,
				NULL);

	if (pvt->dev_d0f0 == NULL)
		goto fail;

	return 0;

fail:
	pci_dev_put(pvt->dev_d0f1);
	return 1;
}