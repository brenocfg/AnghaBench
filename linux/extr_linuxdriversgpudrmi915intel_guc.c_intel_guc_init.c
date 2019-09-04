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
struct intel_guc {int /*<<< orphan*/  fw; int /*<<< orphan*/  log; int /*<<< orphan*/  ads_vma; int /*<<< orphan*/  shared_data; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int guc_shared_data_create (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_shared_data_destroy (struct intel_guc*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  i915_ggtt_enable_guc (struct drm_i915_private*) ; 
 int intel_guc_ads_create (struct intel_guc*) ; 
 int intel_guc_log_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_log_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 

int intel_guc_init(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	int ret;

	ret = guc_shared_data_create(guc);
	if (ret)
		goto err_fetch;
	GEM_BUG_ON(!guc->shared_data);

	ret = intel_guc_log_create(&guc->log);
	if (ret)
		goto err_shared;

	ret = intel_guc_ads_create(guc);
	if (ret)
		goto err_log;
	GEM_BUG_ON(!guc->ads_vma);

	/* We need to notify the guc whenever we change the GGTT */
	i915_ggtt_enable_guc(dev_priv);

	return 0;

err_log:
	intel_guc_log_destroy(&guc->log);
err_shared:
	guc_shared_data_destroy(guc);
err_fetch:
	intel_uc_fw_fini(&guc->fw);
	return ret;
}