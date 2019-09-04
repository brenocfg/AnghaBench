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
struct TYPE_2__ {scalar_t__ load_status; } ;
struct intel_guc {TYPE_1__ fw; } ;
struct drm_i915_private {struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 scalar_t__ INTEL_UC_FIRMWARE_SUCCESS ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_enable_guc_interrupts (struct drm_i915_private*) ; 
 int intel_guc_resume (struct intel_guc*) ; 

int intel_uc_resume(struct drm_i915_private *i915)
{
	struct intel_guc *guc = &i915->guc;
	int err;

	if (!USES_GUC(i915))
		return 0;

	if (guc->fw.load_status != INTEL_UC_FIRMWARE_SUCCESS)
		return 0;

	gen9_enable_guc_interrupts(i915);

	err = intel_guc_resume(guc);
	if (err) {
		DRM_DEBUG_DRIVER("Failed to resume GuC, err=%d", err);
		return err;
	}

	return 0;
}