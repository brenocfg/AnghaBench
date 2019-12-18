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
struct pci_dev {int dummy; } ;
struct device_domain_info {scalar_t__ pasid_enabled; scalar_t__ pri_enabled; int /*<<< orphan*/  domain; scalar_t__ ats_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_is_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_domain_lock ; 
 int /*<<< orphan*/  domain_update_iotlb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_ats (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pasid (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pri (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_disable_dev_iotlb(struct device_domain_info *info)
{
	struct pci_dev *pdev;

	assert_spin_locked(&device_domain_lock);

	if (!dev_is_pci(info->dev))
		return;

	pdev = to_pci_dev(info->dev);

	if (info->ats_enabled) {
		pci_disable_ats(pdev);
		info->ats_enabled = 0;
		domain_update_iotlb(info->domain);
	}
#ifdef CONFIG_INTEL_IOMMU_SVM
	if (info->pri_enabled) {
		pci_disable_pri(pdev);
		info->pri_enabled = 0;
	}
	if (info->pasid_enabled) {
		pci_disable_pasid(pdev);
		info->pasid_enabled = 0;
	}
#endif
}