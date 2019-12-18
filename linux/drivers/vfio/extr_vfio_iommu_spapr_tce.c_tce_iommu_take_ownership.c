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
struct tce_container {struct iommu_table** tables; } ;
struct iommu_table_group {struct iommu_table** tables; } ;
struct iommu_table {int /*<<< orphan*/  it_map; } ;

/* Variables and functions */
 int IOMMU_TABLE_GROUP_MAX_TABLES ; 
 int /*<<< orphan*/  iommu_release_ownership (struct iommu_table*) ; 
 int iommu_take_ownership (struct iommu_table*) ; 

__attribute__((used)) static int tce_iommu_take_ownership(struct tce_container *container,
		struct iommu_table_group *table_group)
{
	int i, j, rc = 0;

	for (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) {
		struct iommu_table *tbl = table_group->tables[i];

		if (!tbl || !tbl->it_map)
			continue;

		rc = iommu_take_ownership(tbl);
		if (rc) {
			for (j = 0; j < i; ++j)
				iommu_release_ownership(
						table_group->tables[j]);

			return rc;
		}
	}

	for (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i)
		container->tables[i] = table_group->tables[i];

	return 0;
}