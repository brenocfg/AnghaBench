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
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int /*<<< orphan*/  guc_disable_communication (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_submission_disable (struct intel_guc*) ; 

void intel_uc_fini_hw(struct drm_i915_private *i915)
{
	struct intel_guc *guc = &i915->guc;

	if (!USES_GUC(i915))
		return;

	GEM_BUG_ON(!HAS_GUC(i915));

	if (USES_GUC_SUBMISSION(i915))
		intel_guc_submission_disable(guc);

	guc_disable_communication(guc);
}