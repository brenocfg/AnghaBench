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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct device_domain_info {int ats_enabled; int /*<<< orphan*/  ats_qdep; int /*<<< orphan*/  domain; scalar_t__ ats_supported; scalar_t__ pfsid; TYPE_1__* iommu; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  number; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecap; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTD_PAGE_SHIFT ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_is_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_domain_lock ; 
 int /*<<< orphan*/  domain_update_iotlb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecap_dit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ats_queue_depth (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_ats (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_physfn (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_enable_dev_iotlb(struct device_domain_info *info)
{
	struct pci_dev *pdev;

	assert_spin_locked(&device_domain_lock);

	if (!info || !dev_is_pci(info->dev))
		return;

	pdev = to_pci_dev(info->dev);
	/* For IOMMU that supports device IOTLB throttling (DIT), we assign
	 * PFSID to the invalidation desc of a VF such that IOMMU HW can gauge
	 * queue depth at PF level. If DIT is not set, PFSID will be treated as
	 * reserved, which should be set to 0.
	 */
	if (!ecap_dit(info->iommu->ecap))
		info->pfsid = 0;
	else {
		struct pci_dev *pf_pdev;

		/* pdev will be returned if device is not a vf */
		pf_pdev = pci_physfn(pdev);
		info->pfsid = PCI_DEVID(pf_pdev->bus->number, pf_pdev->devfn);
	}

#ifdef CONFIG_INTEL_IOMMU_SVM
	/* The PCIe spec, in its wisdom, declares that the behaviour of
	   the device if you enable PASID support after ATS support is
	   undefined. So always enable PASID support on devices which
	   have it, even if we can't yet know if we're ever going to
	   use it. */
	if (info->pasid_supported && !pci_enable_pasid(pdev, info->pasid_supported & ~1))
		info->pasid_enabled = 1;

	if (info->pri_supported && !pci_reset_pri(pdev) && !pci_enable_pri(pdev, 32))
		info->pri_enabled = 1;
#endif
	if (info->ats_supported && !pci_enable_ats(pdev, VTD_PAGE_SHIFT)) {
		info->ats_enabled = 1;
		domain_update_iotlb(info->domain);
		info->ats_qdep = pci_ats_queue_depth(pdev);
	}
}