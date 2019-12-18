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
struct i915_active {int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __active_retire (struct i915_active*) ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
active_retire(struct i915_active *ref)
{
	GEM_BUG_ON(!atomic_read(&ref->count));
	if (atomic_add_unless(&ref->count, -1, 1))
		return;

	/* One active may be flushed from inside the acquire of another */
	mutex_lock_nested(&ref->mutex, SINGLE_DEPTH_NESTING);
	__active_retire(ref);
}