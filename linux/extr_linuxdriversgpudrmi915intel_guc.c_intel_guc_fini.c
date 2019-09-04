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
struct intel_guc {int /*<<< orphan*/  fw; int /*<<< orphan*/  log; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_shared_data_destroy (struct intel_guc*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  i915_ggtt_disable_guc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_guc_ads_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_log_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 

void intel_guc_fini(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);

	i915_ggtt_disable_guc(dev_priv);
	intel_guc_ads_destroy(guc);
	intel_guc_log_destroy(&guc->log);
	guc_shared_data_destroy(guc);
	intel_uc_fw_fini(&guc->fw);
}