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
struct i915_active {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_retire (struct i915_active*) ; 
 int /*<<< orphan*/  debug_active_assert (struct i915_active*) ; 

void i915_active_release(struct i915_active *ref)
{
	debug_active_assert(ref);
	active_retire(ref);
}