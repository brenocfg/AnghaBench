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
struct mapped_device {int dummy; } ;
struct gendisk {int dummy; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int flags; void* target_count; int /*<<< orphan*/  event_nr; int /*<<< orphan*/  open_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DM_ACTIVE_PRESENT_FLAG ; 
 int DM_DEFERRED_REMOVE ; 
 int DM_INTERNAL_SUSPEND_FLAG ; 
 int DM_QUERY_INACTIVE_TABLE_FLAG ; 
 int DM_READONLY_FLAG ; 
 int DM_SUSPEND_FLAG ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  disk_devt (struct gendisk*) ; 
 struct gendisk* dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_get_event_nr (struct mapped_device*) ; 
 struct dm_table* dm_get_inactive_table (struct mapped_device*,int*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 
 int /*<<< orphan*/  dm_open_count (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 scalar_t__ dm_suspended_internally_md (struct mapped_device*) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 int dm_table_get_mode (struct dm_table*) ; 
 void* dm_table_get_num_targets (struct dm_table*) ; 
 scalar_t__ dm_test_deferred_remove_flag (struct mapped_device*) ; 
 scalar_t__ get_disk_ro (struct gendisk*) ; 
 int /*<<< orphan*/  huge_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dev_status(struct mapped_device *md, struct dm_ioctl *param)
{
	struct gendisk *disk = dm_disk(md);
	struct dm_table *table;
	int srcu_idx;

	param->flags &= ~(DM_SUSPEND_FLAG | DM_READONLY_FLAG |
			  DM_ACTIVE_PRESENT_FLAG | DM_INTERNAL_SUSPEND_FLAG);

	if (dm_suspended_md(md))
		param->flags |= DM_SUSPEND_FLAG;

	if (dm_suspended_internally_md(md))
		param->flags |= DM_INTERNAL_SUSPEND_FLAG;

	if (dm_test_deferred_remove_flag(md))
		param->flags |= DM_DEFERRED_REMOVE;

	param->dev = huge_encode_dev(disk_devt(disk));

	/*
	 * Yes, this will be out of date by the time it gets back
	 * to userland, but it is still very useful for
	 * debugging.
	 */
	param->open_count = dm_open_count(md);

	param->event_nr = dm_get_event_nr(md);
	param->target_count = 0;

	table = dm_get_live_table(md, &srcu_idx);
	if (table) {
		if (!(param->flags & DM_QUERY_INACTIVE_TABLE_FLAG)) {
			if (get_disk_ro(disk))
				param->flags |= DM_READONLY_FLAG;
			param->target_count = dm_table_get_num_targets(table);
		}

		param->flags |= DM_ACTIVE_PRESENT_FLAG;
	}
	dm_put_live_table(md, srcu_idx);

	if (param->flags & DM_QUERY_INACTIVE_TABLE_FLAG) {
		int srcu_idx;
		table = dm_get_inactive_table(md, &srcu_idx);
		if (table) {
			if (!(dm_table_get_mode(table) & FMODE_WRITE))
				param->flags |= DM_READONLY_FLAG;
			param->target_count = dm_table_get_num_targets(table);
		}
		dm_put_live_table(md, srcu_idx);
	}
}