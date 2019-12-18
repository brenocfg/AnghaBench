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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct iommu_dev_data {int /*<<< orphan*/  rs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BUS_NUM (int) ; 
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 scalar_t__ __ratelimit (int /*<<< orphan*/ *) ; 
 struct iommu_dev_data* get_dev_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static void amd_iommu_report_page_fault(u16 devid, u16 domain_id,
					u64 address, int flags)
{
	struct iommu_dev_data *dev_data = NULL;
	struct pci_dev *pdev;

	pdev = pci_get_domain_bus_and_slot(0, PCI_BUS_NUM(devid),
					   devid & 0xff);
	if (pdev)
		dev_data = get_dev_data(&pdev->dev);

	if (dev_data && __ratelimit(&dev_data->rs)) {
		pci_err(pdev, "Event logged [IO_PAGE_FAULT domain=0x%04x address=0x%llx flags=0x%04x]\n",
			domain_id, address, flags);
	} else if (printk_ratelimit()) {
		pr_err("Event logged [IO_PAGE_FAULT device=%02x:%02x.%x domain=0x%04x address=0x%llx flags=0x%04x]\n",
			PCI_BUS_NUM(devid), PCI_SLOT(devid), PCI_FUNC(devid),
			domain_id, address, flags);
	}

	if (pdev)
		pci_dev_put(pdev);
}