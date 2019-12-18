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
struct i915_active {int (* active ) (struct i915_active*) ;int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_active_activate (struct i915_active*) ; 
 int /*<<< orphan*/  debug_active_assert (struct i915_active*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct i915_active*) ; 

int i915_active_acquire(struct i915_active *ref)
{
	int err;

	debug_active_assert(ref);
	if (atomic_add_unless(&ref->count, 1, 0))
		return 0;

	err = mutex_lock_interruptible(&ref->mutex);
	if (err)
		return err;

	if (!atomic_read(&ref->count) && ref->active)
		err = ref->active(ref);
	if (!err) {
		debug_active_activate(ref);
		atomic_inc(&ref->count);
	}

	mutex_unlock(&ref->mutex);

	return err;
}