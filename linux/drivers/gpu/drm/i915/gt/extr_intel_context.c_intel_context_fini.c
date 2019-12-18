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
struct intel_context {int /*<<< orphan*/  active; int /*<<< orphan*/  pin_mutex; int /*<<< orphan*/  vm; scalar_t__ timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_active_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_vm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_timeline_put (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void intel_context_fini(struct intel_context *ce)
{
	if (ce->timeline)
		intel_timeline_put(ce->timeline);
	i915_vm_put(ce->vm);

	mutex_destroy(&ce->pin_mutex);
	i915_active_fini(&ce->active);
}