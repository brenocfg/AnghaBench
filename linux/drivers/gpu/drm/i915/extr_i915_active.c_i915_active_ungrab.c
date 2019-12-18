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
struct i915_active {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_ACTIVE_GRAB_BIT ; 
 int /*<<< orphan*/  __active_ungrab (struct i915_active*) ; 
 int /*<<< orphan*/  active_retire (struct i915_active*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void i915_active_ungrab(struct i915_active *ref)
{
	GEM_BUG_ON(!test_bit(I915_ACTIVE_GRAB_BIT, &ref->flags));

	active_retire(ref);
	__active_ungrab(ref);
}