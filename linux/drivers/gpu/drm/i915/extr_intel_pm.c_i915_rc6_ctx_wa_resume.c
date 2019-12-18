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
struct TYPE_3__ {int ctx_corrupted; int /*<<< orphan*/  ctx_corrupted_wakeref; } ;
struct TYPE_4__ {TYPE_1__ rc6; } ;
struct drm_i915_private {TYPE_2__ gt_pm; int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ i915_rc6_ctx_corrupted (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 

void i915_rc6_ctx_wa_resume(struct drm_i915_private *i915)
{
	if (!i915->gt_pm.rc6.ctx_corrupted)
		return;

	if (i915_rc6_ctx_corrupted(i915)) {
		i915->gt_pm.rc6.ctx_corrupted_wakeref =
			intel_runtime_pm_get(&i915->runtime_pm);
		return;
	}

	DRM_INFO("RC6 context restored, re-enabling runtime power management\n");
	i915->gt_pm.rc6.ctx_corrupted = false;
}