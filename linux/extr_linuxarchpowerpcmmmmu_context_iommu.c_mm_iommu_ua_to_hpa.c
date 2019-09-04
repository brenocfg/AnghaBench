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
typedef  unsigned long u64 ;
struct mm_iommu_table_group_mem_t {unsigned long ua; unsigned long* hpas; long const entries; unsigned int pageshift; } ;

/* Variables and functions */
 long EFAULT ; 
 unsigned long MM_IOMMU_TABLE_GROUP_PAGE_MASK ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 

long mm_iommu_ua_to_hpa(struct mm_iommu_table_group_mem_t *mem,
		unsigned long ua, unsigned int pageshift, unsigned long *hpa)
{
	const long entry = (ua - mem->ua) >> PAGE_SHIFT;
	u64 *va = &mem->hpas[entry];

	if (entry >= mem->entries)
		return -EFAULT;

	if (pageshift > mem->pageshift)
		return -EFAULT;

	*hpa = (*va & MM_IOMMU_TABLE_GROUP_PAGE_MASK) | (ua & ~PAGE_MASK);

	return 0;
}