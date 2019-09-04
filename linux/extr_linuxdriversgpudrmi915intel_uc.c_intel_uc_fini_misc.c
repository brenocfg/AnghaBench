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
struct intel_huc {int dummy; } ;
struct intel_guc {int dummy; } ;
struct drm_i915_private {struct intel_huc huc; struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 scalar_t__ USES_HUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_guc_fini_misc (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_huc_fini_misc (struct intel_huc*) ; 

void intel_uc_fini_misc(struct drm_i915_private *i915)
{
	struct intel_guc *guc = &i915->guc;
	struct intel_huc *huc = &i915->huc;

	if (!USES_GUC(i915))
		return;

	if (USES_HUC(i915))
		intel_huc_fini_misc(huc);

	intel_guc_fini_misc(guc);
}