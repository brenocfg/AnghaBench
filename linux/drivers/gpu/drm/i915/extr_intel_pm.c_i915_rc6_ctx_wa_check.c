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
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; TYPE_2__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_NOTE (char*) ; 
 int /*<<< orphan*/  NEEDS_RC6_CTX_CORRUPTION_WA (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_rc6_ctx_corrupted (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_disable_rc6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get_noresume (int /*<<< orphan*/ *) ; 

bool i915_rc6_ctx_wa_check(struct drm_i915_private *i915)
{
	if (!NEEDS_RC6_CTX_CORRUPTION_WA(i915))
		return false;

	if (i915->gt_pm.rc6.ctx_corrupted)
		return false;

	if (!i915_rc6_ctx_corrupted(i915))
		return false;

	DRM_NOTE("RC6 context corruption, disabling runtime power management\n");

	intel_disable_rc6(i915);
	i915->gt_pm.rc6.ctx_corrupted = true;
	i915->gt_pm.rc6.ctx_corrupted_wakeref =
		intel_runtime_pm_get_noresume(&i915->runtime_pm);

	return true;
}