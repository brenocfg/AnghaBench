#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_8__ {int /*<<< orphan*/  uc; TYPE_1__ hangcheck; } ;
struct TYPE_7__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  userfault_wakeref; } ;
struct drm_i915_private {TYPE_4__ gt; TYPE_3__ drm; int /*<<< orphan*/  wq; TYPE_2__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_wakeref_auto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_to_kernel_context_sync (TYPE_4__*) ; 

void i915_gem_suspend(struct drm_i915_private *i915)
{
	GEM_TRACE("\n");

	intel_wakeref_auto(&i915->ggtt.userfault_wakeref, 0);
	flush_workqueue(i915->wq);

	mutex_lock(&i915->drm.struct_mutex);

	/*
	 * We have to flush all the executing contexts to main memory so
	 * that they can saved in the hibernation image. To ensure the last
	 * context image is coherent, we have to switch away from it. That
	 * leaves the i915->kernel_context still active when
	 * we actually suspend, and its image in memory may not match the GPU
	 * state. Fortunately, the kernel_context is disposable and we do
	 * not rely on its state.
	 */
	switch_to_kernel_context_sync(&i915->gt);

	mutex_unlock(&i915->drm.struct_mutex);

	cancel_delayed_work_sync(&i915->gt.hangcheck.work);

	i915_gem_drain_freed_objects(i915);

	intel_uc_suspend(&i915->gt.uc);
}