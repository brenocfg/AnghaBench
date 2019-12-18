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
struct io_pgtable_cfg {int quirks; } ;
typedef  int arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_ATTR_B ; 
 int ARM_V7S_ATTR_C ; 
 int ARM_V7S_ATTR_NG ; 
 int ARM_V7S_ATTR_NS_SECTION ; 
 int ARM_V7S_ATTR_S ; 
 int ARM_V7S_ATTR_SHIFT (int) ; 
 int ARM_V7S_ATTR_TEX (int) ; 
 int ARM_V7S_ATTR_XN (int) ; 
 int ARM_V7S_PTE_AF ; 
 int ARM_V7S_PTE_AP_RDONLY ; 
 int ARM_V7S_PTE_AP_UNPRIV ; 
 int ARM_V7S_PTE_TYPE_PAGE ; 
 int IOMMU_CACHE ; 
 int IOMMU_MMIO ; 
 int IOMMU_NOEXEC ; 
 int IOMMU_PRIV ; 
 int IOMMU_WRITE ; 
 int IO_PGTABLE_QUIRK_ARM_NS ; 
 int IO_PGTABLE_QUIRK_NO_PERMS ; 

__attribute__((used)) static arm_v7s_iopte arm_v7s_prot_to_pte(int prot, int lvl,
					 struct io_pgtable_cfg *cfg)
{
	bool ap = !(cfg->quirks & IO_PGTABLE_QUIRK_NO_PERMS);
	arm_v7s_iopte pte = ARM_V7S_ATTR_NG | ARM_V7S_ATTR_S;

	if (!(prot & IOMMU_MMIO))
		pte |= ARM_V7S_ATTR_TEX(1);
	if (ap) {
		pte |= ARM_V7S_PTE_AF;
		if (!(prot & IOMMU_PRIV))
			pte |= ARM_V7S_PTE_AP_UNPRIV;
		if (!(prot & IOMMU_WRITE))
			pte |= ARM_V7S_PTE_AP_RDONLY;
	}
	pte <<= ARM_V7S_ATTR_SHIFT(lvl);

	if ((prot & IOMMU_NOEXEC) && ap)
		pte |= ARM_V7S_ATTR_XN(lvl);
	if (prot & IOMMU_MMIO)
		pte |= ARM_V7S_ATTR_B;
	else if (prot & IOMMU_CACHE)
		pte |= ARM_V7S_ATTR_B | ARM_V7S_ATTR_C;

	pte |= ARM_V7S_PTE_TYPE_PAGE;
	if (lvl == 1 && (cfg->quirks & IO_PGTABLE_QUIRK_ARM_NS))
		pte |= ARM_V7S_ATTR_NS_SECTION;

	return pte;
}