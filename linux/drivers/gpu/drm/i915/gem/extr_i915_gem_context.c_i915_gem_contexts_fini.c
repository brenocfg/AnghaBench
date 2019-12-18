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
struct TYPE_4__ {int /*<<< orphan*/  hw_ida; int /*<<< orphan*/  hw_id_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ contexts; int /*<<< orphan*/  kernel_context; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  destroy_kernel_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void i915_gem_contexts_fini(struct drm_i915_private *i915)
{
	lockdep_assert_held(&i915->drm.struct_mutex);

	destroy_kernel_context(&i915->kernel_context);

	/* Must free all deferred contexts (via flush_workqueue) first */
	GEM_BUG_ON(!list_empty(&i915->contexts.hw_id_list));
	ida_destroy(&i915->contexts.hw_ida);
}