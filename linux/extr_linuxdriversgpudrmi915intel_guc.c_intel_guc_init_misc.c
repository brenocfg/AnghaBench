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
struct intel_guc {int /*<<< orphan*/  fw; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_init_ggtt_pin_bias (struct intel_guc*) ; 
 int guc_init_wq (struct intel_guc*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uc_fw_fetch (struct drm_i915_private*,int /*<<< orphan*/ *) ; 

int intel_guc_init_misc(struct intel_guc *guc)
{
	struct drm_i915_private *i915 = guc_to_i915(guc);
	int ret;

	guc_init_ggtt_pin_bias(guc);

	ret = guc_init_wq(guc);
	if (ret)
		return ret;

	intel_uc_fw_fetch(i915, &guc->fw);

	return 0;
}