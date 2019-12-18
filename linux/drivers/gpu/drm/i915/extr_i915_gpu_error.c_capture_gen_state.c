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
struct i915_gpu_state {int iommu; int /*<<< orphan*/  driver_caps; int /*<<< orphan*/  runtime_info; int /*<<< orphan*/  device_info; int /*<<< orphan*/  suspend_count; int /*<<< orphan*/  reset_count; int /*<<< orphan*/  suspended; int /*<<< orphan*/  wakelock; int /*<<< orphan*/  awake; struct drm_i915_private* i915; } ;
struct TYPE_4__ {int /*<<< orphan*/  suspended; int /*<<< orphan*/  wakeref_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  awake; } ;
struct drm_i915_private {int /*<<< orphan*/  caps; int /*<<< orphan*/  suspend_count; int /*<<< orphan*/  gpu_error; TYPE_2__ runtime_pm; TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  RUNTIME_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_reset_count (int /*<<< orphan*/ *) ; 
 int intel_iommu_gfx_mapped ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void capture_gen_state(struct i915_gpu_state *error)
{
	struct drm_i915_private *i915 = error->i915;

	error->awake = i915->gt.awake;
	error->wakelock = atomic_read(&i915->runtime_pm.wakeref_count);
	error->suspended = i915->runtime_pm.suspended;

	error->iommu = -1;
#ifdef CONFIG_INTEL_IOMMU
	error->iommu = intel_iommu_gfx_mapped;
#endif
	error->reset_count = i915_reset_count(&i915->gpu_error);
	error->suspend_count = i915->suspend_count;

	memcpy(&error->device_info,
	       INTEL_INFO(i915),
	       sizeof(error->device_info));
	memcpy(&error->runtime_info,
	       RUNTIME_INFO(i915),
	       sizeof(error->runtime_info));
	error->driver_caps = i915->caps;
}