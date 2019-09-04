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
typedef  int arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_ATTR_C ; 
 int ARM_V7S_ATTR_SHIFT (int) ; 
 int ARM_V7S_ATTR_XN (int) ; 
 int ARM_V7S_PTE_AP_RDONLY ; 
 int ARM_V7S_PTE_AP_UNPRIV ; 
 int ARM_V7S_TEX_MASK ; 
 int ARM_V7S_TEX_SHIFT ; 
 int IOMMU_CACHE ; 
 int IOMMU_MMIO ; 
 int IOMMU_NOEXEC ; 
 int IOMMU_PRIV ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 

__attribute__((used)) static int arm_v7s_pte_to_prot(arm_v7s_iopte pte, int lvl)
{
	int prot = IOMMU_READ;
	arm_v7s_iopte attr = pte >> ARM_V7S_ATTR_SHIFT(lvl);

	if (!(attr & ARM_V7S_PTE_AP_RDONLY))
		prot |= IOMMU_WRITE;
	if (!(attr & ARM_V7S_PTE_AP_UNPRIV))
		prot |= IOMMU_PRIV;
	if ((attr & (ARM_V7S_TEX_MASK << ARM_V7S_TEX_SHIFT)) == 0)
		prot |= IOMMU_MMIO;
	else if (pte & ARM_V7S_ATTR_C)
		prot |= IOMMU_CACHE;
	if (pte & ARM_V7S_ATTR_XN(lvl))
		prot |= IOMMU_NOEXEC;

	return prot;
}