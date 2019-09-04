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
struct hash_cell {struct dm_table* new_map; struct mapped_device* md; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int flags; int /*<<< orphan*/  event_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMDEBUG_LIMIT (char*) ; 
 int DM_INACTIVE_PRESENT_FLAG ; 
 int DM_NOFLUSH_FLAG ; 
 int DM_SKIP_LOCKFS_FLAG ; 
 unsigned int DM_SUSPEND_LOCKFS_FLAG ; 
 unsigned int DM_SUSPEND_NOFLUSH_FLAG ; 
 int DM_UEVENT_GENERATED_FLAG ; 
 int ENXIO ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct dm_table*) ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int PTR_ERR (struct dm_table*) ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 struct hash_cell* __find_device_hash_cell (struct dm_ioctl*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_kobject_uevent (struct mapped_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int dm_resume (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_suspend (struct mapped_device*,unsigned int) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 struct dm_table* dm_swap_table (struct mapped_device*,struct dm_table*) ; 
 int /*<<< orphan*/  dm_sync_table (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_destroy (struct dm_table*) ; 
 int dm_table_get_mode (struct dm_table*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_resume(struct dm_ioctl *param)
{
	int r = 0;
	unsigned suspend_flags = DM_SUSPEND_LOCKFS_FLAG;
	struct hash_cell *hc;
	struct mapped_device *md;
	struct dm_table *new_map, *old_map = NULL;

	down_write(&_hash_lock);

	hc = __find_device_hash_cell(param);
	if (!hc) {
		DMDEBUG_LIMIT("device doesn't appear to be in the dev hash table.");
		up_write(&_hash_lock);
		return -ENXIO;
	}

	md = hc->md;

	new_map = hc->new_map;
	hc->new_map = NULL;
	param->flags &= ~DM_INACTIVE_PRESENT_FLAG;

	up_write(&_hash_lock);

	/* Do we need to load a new map ? */
	if (new_map) {
		/* Suspend if it isn't already suspended */
		if (param->flags & DM_SKIP_LOCKFS_FLAG)
			suspend_flags &= ~DM_SUSPEND_LOCKFS_FLAG;
		if (param->flags & DM_NOFLUSH_FLAG)
			suspend_flags |= DM_SUSPEND_NOFLUSH_FLAG;
		if (!dm_suspended_md(md))
			dm_suspend(md, suspend_flags);

		old_map = dm_swap_table(md, new_map);
		if (IS_ERR(old_map)) {
			dm_sync_table(md);
			dm_table_destroy(new_map);
			dm_put(md);
			return PTR_ERR(old_map);
		}

		if (dm_table_get_mode(new_map) & FMODE_WRITE)
			set_disk_ro(dm_disk(md), 0);
		else
			set_disk_ro(dm_disk(md), 1);
	}

	if (dm_suspended_md(md)) {
		r = dm_resume(md);
		if (!r && !dm_kobject_uevent(md, KOBJ_CHANGE, param->event_nr))
			param->flags |= DM_UEVENT_GENERATED_FLAG;
	}

	/*
	 * Since dm_swap_table synchronizes RCU, nobody should be in
	 * read-side critical section already.
	 */
	if (old_map)
		dm_table_destroy(old_map);

	if (!r)
		__dev_status(md, param);

	dm_put(md);
	return r;
}