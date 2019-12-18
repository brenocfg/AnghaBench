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
struct iommu_table {unsigned long it_allocated_size; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  account_locked_vm (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 

__attribute__((used)) static void tce_iommu_free_table(struct tce_container *container,
		struct iommu_table *tbl)
{
	unsigned long pages = tbl->it_allocated_size >> PAGE_SHIFT;

	iommu_tce_table_put(tbl);
	account_locked_vm(container->mm, pages, false);
}