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
struct mapped_device {int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  map; int /*<<< orphan*/  flags; int /*<<< orphan*/  internal_suspend_count; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_SUSPENDED_INTERNALLY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __dm_suspend (struct mapped_device*,struct dm_table*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_postsuspend_targets (struct dm_table*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct dm_table* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dm_internal_suspend(struct mapped_device *md, unsigned suspend_flags)
{
	struct dm_table *map = NULL;

	lockdep_assert_held(&md->suspend_lock);

	if (md->internal_suspend_count++)
		return; /* nested internal suspend */

	if (dm_suspended_md(md)) {
		set_bit(DMF_SUSPENDED_INTERNALLY, &md->flags);
		return; /* nest suspend */
	}

	map = rcu_dereference_protected(md->map, lockdep_is_held(&md->suspend_lock));

	/*
	 * Using TASK_UNINTERRUPTIBLE because only NOFLUSH internal suspend is
	 * supported.  Properly supporting a TASK_INTERRUPTIBLE internal suspend
	 * would require changing .presuspend to return an error -- avoid this
	 * until there is a need for more elaborate variants of internal suspend.
	 */
	(void) __dm_suspend(md, map, suspend_flags, TASK_UNINTERRUPTIBLE,
			    DMF_SUSPENDED_INTERNALLY);

	dm_table_postsuspend_targets(map);
}