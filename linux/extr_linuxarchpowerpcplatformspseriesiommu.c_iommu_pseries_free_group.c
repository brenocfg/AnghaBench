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
struct iommu_table_group {struct iommu_table** tables; } ;
struct iommu_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 
 int /*<<< orphan*/  kfree (struct iommu_table_group*) ; 

__attribute__((used)) static void iommu_pseries_free_group(struct iommu_table_group *table_group,
		const char *node_name)
{
	struct iommu_table *tbl;
#ifdef CONFIG_IOMMU_API
	struct iommu_table_group_link *tgl;
#endif

	if (!table_group)
		return;

	tbl = table_group->tables[0];
#ifdef CONFIG_IOMMU_API
	tgl = list_first_entry_or_null(&tbl->it_group_list,
			struct iommu_table_group_link, next);

	WARN_ON_ONCE(!tgl);
	if (tgl) {
		list_del_rcu(&tgl->next);
		kfree(tgl);
	}
	if (table_group->group) {
		iommu_group_put(table_group->group);
		BUG_ON(table_group->group);
	}
#endif
	iommu_tce_table_put(tbl);

	kfree(table_group);
}