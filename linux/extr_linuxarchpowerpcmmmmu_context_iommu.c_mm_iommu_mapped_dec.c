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
struct mm_iommu_table_group_mem_t {int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_add_unless (int /*<<< orphan*/ *,int,int) ; 

void mm_iommu_mapped_dec(struct mm_iommu_table_group_mem_t *mem)
{
	atomic64_add_unless(&mem->mapped, -1, 1);
}