#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hw_ida; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ contexts; scalar_t__ kernel_context; scalar_t__ preempt_context; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_kernel_context (scalar_t__*) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void i915_gem_contexts_fini(struct drm_i915_private *i915)
{
	lockdep_assert_held(&i915->drm.struct_mutex);

	if (i915->preempt_context)
		destroy_kernel_context(&i915->preempt_context);
	destroy_kernel_context(&i915->kernel_context);

	/* Must free all deferred contexts (via flush_workqueue) first */
	ida_destroy(&i915->contexts.hw_ida);
}