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
struct intel_context {int /*<<< orphan*/  active; int /*<<< orphan*/  engine; int /*<<< orphan*/  gem_context; } ;

/* Variables and functions */
 int i915_active_acquire (int /*<<< orphan*/ *) ; 
 int i915_active_acquire_preallocate_barrier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_active_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_context_is_kernel (int /*<<< orphan*/ ) ; 

int intel_context_active_acquire(struct intel_context *ce)
{
	int err;

	err = i915_active_acquire(&ce->active);
	if (err)
		return err;

	/* Preallocate tracking nodes */
	if (!i915_gem_context_is_kernel(ce->gem_context)) {
		err = i915_active_acquire_preallocate_barrier(&ce->active,
							      ce->engine);
		if (err) {
			i915_active_release(&ce->active);
			return err;
		}
	}

	return 0;
}