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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct kfd_dev {int dummy; } ;

/* Variables and functions */
 int AMD_IOMMU_INV_PRI_RSP_INVALID ; 
 int /*<<< orphan*/  PCI_BUS_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int PPR_FAULT_EXEC ; 
 int PPR_FAULT_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  kfd_device ; 
 struct kfd_dev* kfd_device_by_pci_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  kfd_signal_iommu_event (struct kfd_dev*,int,unsigned long,int,int) ; 

__attribute__((used)) static int iommu_invalid_ppr_cb(struct pci_dev *pdev, int pasid,
		unsigned long address, u16 flags)
{
	struct kfd_dev *dev;

	dev_warn_ratelimited(kfd_device,
			"Invalid PPR device %x:%x.%x pasid %d address 0x%lX flags 0x%X",
			PCI_BUS_NUM(pdev->devfn),
			PCI_SLOT(pdev->devfn),
			PCI_FUNC(pdev->devfn),
			pasid,
			address,
			flags);

	dev = kfd_device_by_pci_dev(pdev);
	if (!WARN_ON(!dev))
		kfd_signal_iommu_event(dev, pasid, address,
			flags & PPR_FAULT_WRITE, flags & PPR_FAULT_EXEC);

	return AMD_IOMMU_INV_PRI_RSP_INVALID;
}