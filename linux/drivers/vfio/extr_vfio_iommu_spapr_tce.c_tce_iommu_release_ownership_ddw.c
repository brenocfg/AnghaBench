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
struct tce_container {scalar_t__* tables; } ;
struct iommu_table_group {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_ownership ) (struct iommu_table_group*) ;int /*<<< orphan*/  (* unset_window ) (struct iommu_table_group*,long) ;} ;

/* Variables and functions */
 long IOMMU_TABLE_GROUP_MAX_TABLES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  stub1 (struct iommu_table_group*,long) ; 
 int /*<<< orphan*/  stub2 (struct iommu_table_group*) ; 

__attribute__((used)) static void tce_iommu_release_ownership_ddw(struct tce_container *container,
		struct iommu_table_group *table_group)
{
	long i;

	if (!table_group->ops->unset_window) {
		WARN_ON_ONCE(1);
		return;
	}

	for (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i)
		if (container->tables[i])
			table_group->ops->unset_window(table_group, i);

	table_group->ops->release_ownership(table_group);
}