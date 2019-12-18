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
struct tce_container {int /*<<< orphan*/  mm; } ;
struct mm_iommu_table_group_mem_t {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mm_iommu_table_group_mem_t* mm_iommu_lookup (int /*<<< orphan*/ ,unsigned long,unsigned long long) ; 
 long mm_iommu_ua_to_hpa (struct mm_iommu_table_group_mem_t*,unsigned long,unsigned long,unsigned long*) ; 

__attribute__((used)) static int tce_iommu_prereg_ua_to_hpa(struct tce_container *container,
		unsigned long tce, unsigned long shift,
		unsigned long *phpa, struct mm_iommu_table_group_mem_t **pmem)
{
	long ret = 0;
	struct mm_iommu_table_group_mem_t *mem;

	mem = mm_iommu_lookup(container->mm, tce, 1ULL << shift);
	if (!mem)
		return -EINVAL;

	ret = mm_iommu_ua_to_hpa(mem, tce, shift, phpa);
	if (ret)
		return -EINVAL;

	*pmem = mem;

	return 0;
}