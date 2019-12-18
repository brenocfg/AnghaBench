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
struct intel_uc {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  uncore; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  ENXIO ; 
 int GS_MIA_IN_RESET ; 
 int /*<<< orphan*/  GUC_STATUS ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int i915_inject_load_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_reset_guc (struct intel_gt*) ; 
 int intel_uncore_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_gt* uc_to_gt (struct intel_uc*) ; 

__attribute__((used)) static int __intel_uc_reset_hw(struct intel_uc *uc)
{
	struct intel_gt *gt = uc_to_gt(uc);
	int ret;
	u32 guc_status;

	ret = i915_inject_load_error(gt->i915, -ENXIO);
	if (ret)
		return ret;

	ret = intel_reset_guc(gt);
	if (ret) {
		DRM_ERROR("Failed to reset GuC, ret = %d\n", ret);
		return ret;
	}

	guc_status = intel_uncore_read(gt->uncore, GUC_STATUS);
	WARN(!(guc_status & GS_MIA_IN_RESET),
	     "GuC status: 0x%x, MIA core expected to be in reset\n",
	     guc_status);

	return ret;
}