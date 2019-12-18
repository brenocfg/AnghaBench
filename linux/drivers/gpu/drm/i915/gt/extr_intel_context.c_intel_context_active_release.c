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
struct intel_context {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_active_acquire_barrier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_active_release (int /*<<< orphan*/ *) ; 

void intel_context_active_release(struct intel_context *ce)
{
	/* Nodes preallocated in intel_context_active() */
	i915_active_acquire_barrier(&ce->active);
	i915_active_release(&ce->active);
}