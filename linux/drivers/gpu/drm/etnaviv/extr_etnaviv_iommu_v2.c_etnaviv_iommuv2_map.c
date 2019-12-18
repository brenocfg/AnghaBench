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
typedef  int u32 ;
struct etnaviv_iommuv2_context {int** stlb_cpu; } ;
struct etnaviv_iommu_context {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PHYS_ADDR_T_64BIT ; 
 int EINVAL ; 
 int ETNAVIV_PROT_WRITE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long MMUv2_MTLB_MASK ; 
 unsigned long MMUv2_MTLB_SHIFT ; 
 int MMUv2_PTE_PRESENT ; 
 int MMUv2_PTE_WRITEABLE ; 
 unsigned long MMUv2_STLB_MASK ; 
 unsigned long MMUv2_STLB_SHIFT ; 
 size_t SZ_4K ; 
 int etnaviv_iommuv2_ensure_stlb (struct etnaviv_iommuv2_context*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct etnaviv_iommuv2_context* to_v2_context (struct etnaviv_iommu_context*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etnaviv_iommuv2_map(struct etnaviv_iommu_context *context,
			       unsigned long iova, phys_addr_t paddr,
			       size_t size, int prot)
{
	struct etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	int mtlb_entry, stlb_entry, ret;
	u32 entry = lower_32_bits(paddr) | MMUv2_PTE_PRESENT;

	if (size != SZ_4K)
		return -EINVAL;

	if (IS_ENABLED(CONFIG_PHYS_ADDR_T_64BIT))
		entry |= (upper_32_bits(paddr) & 0xff) << 4;

	if (prot & ETNAVIV_PROT_WRITE)
		entry |= MMUv2_PTE_WRITEABLE;

	mtlb_entry = (iova & MMUv2_MTLB_MASK) >> MMUv2_MTLB_SHIFT;
	stlb_entry = (iova & MMUv2_STLB_MASK) >> MMUv2_STLB_SHIFT;

	ret = etnaviv_iommuv2_ensure_stlb(v2_context, mtlb_entry);
	if (ret)
		return ret;

	v2_context->stlb_cpu[mtlb_entry][stlb_entry] = entry;

	return 0;
}