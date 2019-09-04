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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int GS_MIA_IN_RESET ; 
 int /*<<< orphan*/  GUC_STATUS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int intel_reset_guc (struct drm_i915_private*) ; 

__attribute__((used)) static int __intel_uc_reset_hw(struct drm_i915_private *dev_priv)
{
	int ret;
	u32 guc_status;

	ret = intel_reset_guc(dev_priv);
	if (ret) {
		DRM_ERROR("Failed to reset GuC, ret = %d\n", ret);
		return ret;
	}

	guc_status = I915_READ(GUC_STATUS);
	WARN(!(guc_status & GS_MIA_IN_RESET),
	     "GuC status: 0x%x, MIA core expected to be in reset\n",
	     guc_status);

	return ret;
}