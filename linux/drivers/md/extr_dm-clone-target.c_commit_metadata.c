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
struct clone {int /*<<< orphan*/  commit_lock; TYPE_1__* ti; int /*<<< orphan*/  cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int EPERM ; 
 int /*<<< orphan*/  __metadata_operation_failed (struct clone*,char*,int) ; 
 int /*<<< orphan*/  dm_clone_changed_this_transaction (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_clone_is_hydration_done (int /*<<< orphan*/ ) ; 
 int dm_clone_metadata_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int commit_metadata(struct clone *clone)
{
	int r = 0;

	mutex_lock(&clone->commit_lock);

	if (!dm_clone_changed_this_transaction(clone->cmd))
		goto out;

	if (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) {
		r = -EPERM;
		goto out;
	}

	r = dm_clone_metadata_commit(clone->cmd);

	if (unlikely(r)) {
		__metadata_operation_failed(clone, "dm_clone_metadata_commit", r);
		goto out;
	}

	if (dm_clone_is_hydration_done(clone->cmd))
		dm_table_event(clone->ti->table);
out:
	mutex_unlock(&clone->commit_lock);

	return r;
}