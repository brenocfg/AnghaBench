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
struct mapped_device {int /*<<< orphan*/  holders; int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  flags; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_FREEING ; 
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR_ALLOCED ; 
 int /*<<< orphan*/  __unbind (struct mapped_device*) ; 
 int /*<<< orphan*/  _minor_idr ; 
 int /*<<< orphan*/  _minor_lock ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_set_queue_dying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 int /*<<< orphan*/  dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_sysfs_exit (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_postsuspend_targets (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_presuspend_targets (struct dm_table*) ; 
 int /*<<< orphan*/  free_dev (struct mapped_device*) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dm_destroy(struct mapped_device *md, bool wait)
{
	struct dm_table *map;
	int srcu_idx;

	might_sleep();

	spin_lock(&_minor_lock);
	idr_replace(&_minor_idr, MINOR_ALLOCED, MINOR(disk_devt(dm_disk(md))));
	set_bit(DMF_FREEING, &md->flags);
	spin_unlock(&_minor_lock);

	blk_set_queue_dying(md->queue);

	/*
	 * Take suspend_lock so that presuspend and postsuspend methods
	 * do not race with internal suspend.
	 */
	mutex_lock(&md->suspend_lock);
	map = dm_get_live_table(md, &srcu_idx);
	if (!dm_suspended_md(md)) {
		dm_table_presuspend_targets(map);
		dm_table_postsuspend_targets(map);
	}
	/* dm_put_live_table must be before msleep, otherwise deadlock is possible */
	dm_put_live_table(md, srcu_idx);
	mutex_unlock(&md->suspend_lock);

	/*
	 * Rare, but there may be I/O requests still going to complete,
	 * for example.  Wait for all references to disappear.
	 * No one should increment the reference count of the mapped_device,
	 * after the mapped_device state becomes DMF_FREEING.
	 */
	if (wait)
		while (atomic_read(&md->holders))
			msleep(1);
	else if (atomic_read(&md->holders))
		DMWARN("%s: Forcibly removing mapped_device still in use! (%d users)",
		       dm_device_name(md), atomic_read(&md->holders));

	dm_sysfs_exit(md);
	dm_table_destroy(__unbind(md));
	free_dev(md);
}