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
struct mapped_device {int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  map; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_SUSPENDED ; 
 int /*<<< orphan*/  DMF_SUSPENDED_INTERNALLY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int __dm_resume (struct mapped_device*,struct dm_table*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dm_suspended_internally_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_get_size (struct dm_table*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dm_table* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dm_resume(struct mapped_device *md)
{
	int r;
	struct dm_table *map = NULL;

retry:
	r = -EINVAL;
	mutex_lock_nested(&md->suspend_lock, SINGLE_DEPTH_NESTING);

	if (!dm_suspended_md(md))
		goto out;

	if (dm_suspended_internally_md(md)) {
		/* already internally suspended, wait for internal resume */
		mutex_unlock(&md->suspend_lock);
		r = wait_on_bit(&md->flags, DMF_SUSPENDED_INTERNALLY, TASK_INTERRUPTIBLE);
		if (r)
			return r;
		goto retry;
	}

	map = rcu_dereference_protected(md->map, lockdep_is_held(&md->suspend_lock));
	if (!map || !dm_table_get_size(map))
		goto out;

	r = __dm_resume(md, map);
	if (r)
		goto out;

	clear_bit(DMF_SUSPENDED, &md->flags);
out:
	mutex_unlock(&md->suspend_lock);

	return r;
}