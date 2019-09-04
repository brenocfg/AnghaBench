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
struct amd_iommu_device_info {int /*<<< orphan*/  flags; void* max_pasids; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IOMMU_DEVICE_FLAG_ATS_SUP ; 
 int /*<<< orphan*/  AMD_IOMMU_DEVICE_FLAG_EXEC_SUP ; 
 int /*<<< orphan*/  AMD_IOMMU_DEVICE_FLAG_PASID_SUP ; 
 int /*<<< orphan*/  AMD_IOMMU_DEVICE_FLAG_PRIV_SUP ; 
 int /*<<< orphan*/  AMD_IOMMU_DEVICE_FLAG_PRI_SUP ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ATS ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_PASID ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_PRI ; 
 int PCI_PASID_CAP_EXEC ; 
 int PCI_PASID_CAP_PRIV ; 
 int amd_iommu_max_glx_val ; 
 int /*<<< orphan*/  amd_iommu_v2_supported () ; 
 int /*<<< orphan*/  memset (struct amd_iommu_device_info*,int /*<<< orphan*/ ,int) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  pci_ats_disabled () ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_max_pasids (struct pci_dev*) ; 
 int pci_pasid_features (struct pci_dev*) ; 

int amd_iommu_device_info(struct pci_dev *pdev,
                          struct amd_iommu_device_info *info)
{
	int max_pasids;
	int pos;

	if (pdev == NULL || info == NULL)
		return -EINVAL;

	if (!amd_iommu_v2_supported())
		return -EINVAL;

	memset(info, 0, sizeof(*info));

	if (!pci_ats_disabled()) {
		pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ATS);
		if (pos)
			info->flags |= AMD_IOMMU_DEVICE_FLAG_ATS_SUP;
	}

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_PRI);
	if (pos)
		info->flags |= AMD_IOMMU_DEVICE_FLAG_PRI_SUP;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_PASID);
	if (pos) {
		int features;

		max_pasids = 1 << (9 * (amd_iommu_max_glx_val + 1));
		max_pasids = min(max_pasids, (1 << 20));

		info->flags |= AMD_IOMMU_DEVICE_FLAG_PASID_SUP;
		info->max_pasids = min(pci_max_pasids(pdev), max_pasids);

		features = pci_pasid_features(pdev);
		if (features & PCI_PASID_CAP_EXEC)
			info->flags |= AMD_IOMMU_DEVICE_FLAG_EXEC_SUP;
		if (features & PCI_PASID_CAP_PRIV)
			info->flags |= AMD_IOMMU_DEVICE_FLAG_PRIV_SUP;
	}

	return 0;
}