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
struct intel_guc {int dummy; } ;
struct drm_i915_private {struct intel_guc guc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_guc_fini (struct intel_guc*) ; 
 int intel_guc_init (struct intel_guc*) ; 
 int intel_guc_submission_init (struct intel_guc*) ; 

int intel_uc_init(struct drm_i915_private *i915)
{
	struct intel_guc *guc = &i915->guc;
	int ret;

	if (!USES_GUC(i915))
		return 0;

	if (!HAS_GUC(i915))
		return -ENODEV;

	ret = intel_guc_init(guc);
	if (ret)
		return ret;

	if (USES_GUC_SUBMISSION(i915)) {
		/*
		 * This is stuff we need to have available at fw load time
		 * if we are planning to enable submission later
		 */
		ret = intel_guc_submission_init(guc);
		if (ret) {
			intel_guc_fini(guc);
			return ret;
		}
	}

	return 0;
}