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
struct mapped_device {int dummy; } ;
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int dummy; } ;
struct block_device {TYPE_2__* bd_disk; } ;
typedef  int /*<<< orphan*/  iterate_devices_callout_fn ;
struct TYPE_4__ {struct mapped_device* private_data; } ;
struct TYPE_3__ {int (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 int dm_table_get_num_targets (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_get_size (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dm_target*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dm_call_pr(struct block_device *bdev, iterate_devices_callout_fn fn,
		      void *data)
{
	struct mapped_device *md = bdev->bd_disk->private_data;
	struct dm_table *table;
	struct dm_target *ti;
	int ret = -ENOTTY, srcu_idx;

	table = dm_get_live_table(md, &srcu_idx);
	if (!table || !dm_table_get_size(table))
		goto out;

	/* We only support devices that have a single target */
	if (dm_table_get_num_targets(table) != 1)
		goto out;
	ti = dm_table_get_target(table, 0);

	ret = -EINVAL;
	if (!ti->type->iterate_devices)
		goto out;

	ret = ti->type->iterate_devices(ti, fn, data);
out:
	dm_put_live_table(md, srcu_idx);
	return ret;
}