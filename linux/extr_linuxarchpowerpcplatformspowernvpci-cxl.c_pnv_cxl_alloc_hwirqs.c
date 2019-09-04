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
struct pnv_phb {int msi_base; int /*<<< orphan*/  msi_bmp; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int msi_bitmap_alloc_hwirqs (int /*<<< orphan*/ *,int) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 

int pnv_cxl_alloc_hwirqs(struct pci_dev *dev, int num)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct pnv_phb *phb = hose->private_data;
	int hwirq = msi_bitmap_alloc_hwirqs(&phb->msi_bmp, num);

	if (hwirq < 0) {
		dev_warn(&dev->dev, "Failed to find a free MSI\n");
		return -ENOSPC;
	}

	return phb->msi_base + hwirq;
}