#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_uc {int dummy; } ;
struct intel_huc {int /*<<< orphan*/  fw; } ;
struct intel_gt {struct drm_i915_private* i915; struct intel_uc uc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  platform; } ;

/* Variables and functions */
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_REVID (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_UC_FW_TYPE_HUC ; 
 struct intel_gt* huc_to_gt (struct intel_huc*) ; 
 int /*<<< orphan*/  intel_uc_fw_init_early (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_uses_guc (struct intel_uc*) ; 

void intel_huc_fw_init_early(struct intel_huc *huc)
{
	struct intel_gt *gt = huc_to_gt(huc);
	struct intel_uc *uc = &gt->uc;
	struct drm_i915_private *i915 = gt->i915;

	intel_uc_fw_init_early(&huc->fw, INTEL_UC_FW_TYPE_HUC,
			       intel_uc_uses_guc(uc),
			       INTEL_INFO(i915)->platform, INTEL_REVID(i915));
}