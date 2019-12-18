#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tce_container {int /*<<< orphan*/  mm; } ;
struct iommu_table_group {TYPE_2__* ops; } ;
struct iommu_table {long it_allocated_size; TYPE_1__* it_ops; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {long (* get_table_size ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;long (* create_table ) (struct iommu_table_group*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iommu_table**) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  free; } ;

/* Variables and functions */
 long EINVAL ; 
 long PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 long account_locked_vm (int /*<<< orphan*/ ,long,int) ; 
 long stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long stub2 (struct iommu_table_group*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iommu_table**) ; 

__attribute__((used)) static long tce_iommu_create_table(struct tce_container *container,
			struct iommu_table_group *table_group,
			int num,
			__u32 page_shift,
			__u64 window_size,
			__u32 levels,
			struct iommu_table **ptbl)
{
	long ret, table_size;

	table_size = table_group->ops->get_table_size(page_shift, window_size,
			levels);
	if (!table_size)
		return -EINVAL;

	ret = account_locked_vm(container->mm, table_size >> PAGE_SHIFT, true);
	if (ret)
		return ret;

	ret = table_group->ops->create_table(table_group, num,
			page_shift, window_size, levels, ptbl);

	WARN_ON(!ret && !(*ptbl)->it_ops->free);
	WARN_ON(!ret && ((*ptbl)->it_allocated_size > table_size));

	return ret;
}