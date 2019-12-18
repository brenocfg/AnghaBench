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

/* Variables and functions */
 int /*<<< orphan*/  amba_bustype ; 
 int /*<<< orphan*/  arm_smmu_ops ; 
 int /*<<< orphan*/  bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_bus_type ; 
 int /*<<< orphan*/  iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  pci_request_acs () ; 
 int /*<<< orphan*/  platform_bus_type ; 

__attribute__((used)) static void arm_smmu_bus_init(void)
{
	/* Oh, for a proper bus abstraction */
	if (!iommu_present(&platform_bus_type))
		bus_set_iommu(&platform_bus_type, &arm_smmu_ops);
#ifdef CONFIG_ARM_AMBA
	if (!iommu_present(&amba_bustype))
		bus_set_iommu(&amba_bustype, &arm_smmu_ops);
#endif
#ifdef CONFIG_PCI
	if (!iommu_present(&pci_bus_type)) {
		pci_request_acs();
		bus_set_iommu(&pci_bus_type, &arm_smmu_ops);
	}
#endif
#ifdef CONFIG_FSL_MC_BUS
	if (!iommu_present(&fsl_mc_bus_type))
		bus_set_iommu(&fsl_mc_bus_type, &arm_smmu_ops);
#endif
}