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
struct i915_active {int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_ACTIVE_GRAB_BIT ; 
 int /*<<< orphan*/  __active_ungrab (struct i915_active*) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_active_assert (struct i915_active*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool i915_active_trygrab(struct i915_active *ref)
{
	debug_active_assert(ref);

	if (test_and_set_bit(I915_ACTIVE_GRAB_BIT, &ref->flags))
		return false;

	if (!atomic_add_unless(&ref->count, 1, 0)) {
		__active_ungrab(ref);
		return false;
	}

	return true;
}