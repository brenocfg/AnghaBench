#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_guc {int /*<<< orphan*/  fw; int /*<<< orphan*/  log; int /*<<< orphan*/  ct; int /*<<< orphan*/  ads_vma; int /*<<< orphan*/  shared_data; } ;
struct intel_gt {TYPE_2__* i915; int /*<<< orphan*/  ggtt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  guc_init_params (struct intel_guc*) ; 
 int guc_shared_data_create (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_shared_data_destroy (struct intel_guc*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  i915_ggtt_enable_guc (int /*<<< orphan*/ ) ; 
 int intel_guc_ads_create (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_ads_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_ct_fini (int /*<<< orphan*/ *) ; 
 int intel_guc_ct_init (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_guc_is_submission_supported (struct intel_guc*) ; 
 int intel_guc_log_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_log_destroy (int /*<<< orphan*/ *) ; 
 int intel_guc_submission_init (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uc_fw_cleanup_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 
 int intel_uc_fw_init (int /*<<< orphan*/ *) ; 

int intel_guc_init(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);
	int ret;

	ret = intel_uc_fw_init(&guc->fw);
	if (ret)
		goto err_fetch;

	ret = guc_shared_data_create(guc);
	if (ret)
		goto err_fw;
	GEM_BUG_ON(!guc->shared_data);

	ret = intel_guc_log_create(&guc->log);
	if (ret)
		goto err_shared;

	ret = intel_guc_ads_create(guc);
	if (ret)
		goto err_log;
	GEM_BUG_ON(!guc->ads_vma);

	ret = intel_guc_ct_init(&guc->ct);
	if (ret)
		goto err_ads;

	if (intel_guc_is_submission_supported(guc)) {
		/*
		 * This is stuff we need to have available at fw load time
		 * if we are planning to enable submission later
		 */
		ret = intel_guc_submission_init(guc);
		if (ret)
			goto err_ct;
	}

	/* now that everything is perma-pinned, initialize the parameters */
	guc_init_params(guc);

	/* We need to notify the guc whenever we change the GGTT */
	i915_ggtt_enable_guc(gt->ggtt);

	return 0;

err_ct:
	intel_guc_ct_fini(&guc->ct);
err_ads:
	intel_guc_ads_destroy(guc);
err_log:
	intel_guc_log_destroy(&guc->log);
err_shared:
	guc_shared_data_destroy(guc);
err_fw:
	intel_uc_fw_fini(&guc->fw);
err_fetch:
	intel_uc_fw_cleanup_fetch(&guc->fw);
	DRM_DEV_DEBUG_DRIVER(gt->i915->drm.dev, "failed with %d\n", ret);
	return ret;
}