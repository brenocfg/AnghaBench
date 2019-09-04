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
struct mm_iommu_table_group_mem_t {int /*<<< orphan*/  rcu; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_iommu_free ; 

__attribute__((used)) static void mm_iommu_release(struct mm_iommu_table_group_mem_t *mem)
{
	list_del_rcu(&mem->next);
	call_rcu(&mem->rcu, mm_iommu_free);
}