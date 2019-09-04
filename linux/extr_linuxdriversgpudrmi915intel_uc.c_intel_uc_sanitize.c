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
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __intel_uc_reset_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  guc_disable_communication (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_sanitize (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_huc_sanitize (struct intel_huc*) ; 

void intel_uc_sanitize(struct drm_i915_private *i915)
{
	struct intel_guc *guc = &i915->guc;
	struct intel_huc *huc = &i915->huc;

	if (!USES_GUC(i915))
		return;

	GEM_BUG_ON(!HAS_GUC(i915));

	guc_disable_communication(guc);

	intel_huc_sanitize(huc);
	intel_guc_sanitize(guc);

	__intel_uc_reset_hw(i915);
}