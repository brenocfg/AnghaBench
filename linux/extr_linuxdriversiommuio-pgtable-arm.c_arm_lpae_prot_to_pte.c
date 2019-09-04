#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fmt; } ;
struct arm_lpae_io_pgtable {TYPE_1__ iop; } ;
typedef  int arm_lpae_iopte ;

/* Variables and functions */
 scalar_t__ ARM_32_LPAE_S1 ; 
 scalar_t__ ARM_64_LPAE_S1 ; 
 int ARM_LPAE_MAIR_ATTR_IDX_CACHE ; 
 int ARM_LPAE_MAIR_ATTR_IDX_DEV ; 
 int ARM_LPAE_PTE_AP_RDONLY ; 
 int ARM_LPAE_PTE_AP_UNPRIV ; 
 int ARM_LPAE_PTE_ATTRINDX_SHIFT ; 
 int ARM_LPAE_PTE_HAP_FAULT ; 
 int ARM_LPAE_PTE_HAP_READ ; 
 int ARM_LPAE_PTE_HAP_WRITE ; 
 int ARM_LPAE_PTE_MEMATTR_DEV ; 
 int ARM_LPAE_PTE_MEMATTR_NC ; 
 int ARM_LPAE_PTE_MEMATTR_OIWB ; 
 int ARM_LPAE_PTE_XN ; 
 int ARM_LPAE_PTE_nG ; 
 int IOMMU_CACHE ; 
 int IOMMU_MMIO ; 
 int IOMMU_NOEXEC ; 
 int IOMMU_PRIV ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 

__attribute__((used)) static arm_lpae_iopte arm_lpae_prot_to_pte(struct arm_lpae_io_pgtable *data,
					   int prot)
{
	arm_lpae_iopte pte;

	if (data->iop.fmt == ARM_64_LPAE_S1 ||
	    data->iop.fmt == ARM_32_LPAE_S1) {
		pte = ARM_LPAE_PTE_nG;

		if (!(prot & IOMMU_WRITE) && (prot & IOMMU_READ))
			pte |= ARM_LPAE_PTE_AP_RDONLY;

		if (!(prot & IOMMU_PRIV))
			pte |= ARM_LPAE_PTE_AP_UNPRIV;

		if (prot & IOMMU_MMIO)
			pte |= (ARM_LPAE_MAIR_ATTR_IDX_DEV
				<< ARM_LPAE_PTE_ATTRINDX_SHIFT);
		else if (prot & IOMMU_CACHE)
			pte |= (ARM_LPAE_MAIR_ATTR_IDX_CACHE
				<< ARM_LPAE_PTE_ATTRINDX_SHIFT);
	} else {
		pte = ARM_LPAE_PTE_HAP_FAULT;
		if (prot & IOMMU_READ)
			pte |= ARM_LPAE_PTE_HAP_READ;
		if (prot & IOMMU_WRITE)
			pte |= ARM_LPAE_PTE_HAP_WRITE;
		if (prot & IOMMU_MMIO)
			pte |= ARM_LPAE_PTE_MEMATTR_DEV;
		else if (prot & IOMMU_CACHE)
			pte |= ARM_LPAE_PTE_MEMATTR_OIWB;
		else
			pte |= ARM_LPAE_PTE_MEMATTR_NC;
	}

	if (prot & IOMMU_NOEXEC)
		pte |= ARM_LPAE_PTE_XN;

	return pte;
}