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
struct intel_huc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  minor_ver_found; int /*<<< orphan*/  major_ver_found; } ;
struct intel_guc {TYPE_1__ fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_2__ drm; struct intel_huc huc; struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GEM_WARN_ON (int) ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 scalar_t__ USES_HUC (struct drm_i915_private*) ; 
 int __intel_uc_reset_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  enableddisabled (scalar_t__) ; 
 int /*<<< orphan*/  gen9_reset_guc_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  guc_capture_load_err_log (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_disable_communication (struct intel_guc*) ; 
 int guc_enable_communication (struct intel_guc*) ; 
 int intel_guc_fw_upload (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_init_params (struct intel_guc*) ; 
 int intel_guc_submission_enable (struct intel_guc*) ; 
 int intel_huc_auth (struct intel_huc*) ; 
 int intel_huc_fw_upload (struct intel_huc*) ; 

int intel_uc_init_hw(struct drm_i915_private *i915)
{
	struct intel_guc *guc = &i915->guc;
	struct intel_huc *huc = &i915->huc;
	int ret, attempts;

	if (!USES_GUC(i915))
		return 0;

	GEM_BUG_ON(!HAS_GUC(i915));

	gen9_reset_guc_interrupts(i915);

	/* WaEnableuKernelHeaderValidFix:skl */
	/* WaEnableGuCBootHashCheckNotSet:skl,bxt,kbl */
	if (IS_GEN9(i915))
		attempts = 3;
	else
		attempts = 1;

	while (attempts--) {
		/*
		 * Always reset the GuC just before (re)loading, so
		 * that the state and timing are fairly predictable
		 */
		ret = __intel_uc_reset_hw(i915);
		if (ret)
			goto err_out;

		if (USES_HUC(i915)) {
			ret = intel_huc_fw_upload(huc);
			if (ret)
				goto err_out;
		}

		intel_guc_init_params(guc);
		ret = intel_guc_fw_upload(guc);
		if (ret == 0 || ret != -EAGAIN)
			break;

		DRM_DEBUG_DRIVER("GuC fw load failed: %d; will reset and "
				 "retry %d more time(s)\n", ret, attempts);
	}

	/* Did we succeded or run out of retries? */
	if (ret)
		goto err_log_capture;

	ret = guc_enable_communication(guc);
	if (ret)
		goto err_log_capture;

	if (USES_HUC(i915)) {
		ret = intel_huc_auth(huc);
		if (ret)
			goto err_communication;
	}

	if (USES_GUC_SUBMISSION(i915)) {
		ret = intel_guc_submission_enable(guc);
		if (ret)
			goto err_communication;
	}

	dev_info(i915->drm.dev, "GuC firmware version %u.%u\n",
		 guc->fw.major_ver_found, guc->fw.minor_ver_found);
	dev_info(i915->drm.dev, "GuC submission %s\n",
		 enableddisabled(USES_GUC_SUBMISSION(i915)));
	dev_info(i915->drm.dev, "HuC %s\n",
		 enableddisabled(USES_HUC(i915)));

	return 0;

	/*
	 * We've failed to load the firmware :(
	 */
err_communication:
	guc_disable_communication(guc);
err_log_capture:
	guc_capture_load_err_log(guc);
err_out:
	/*
	 * Note that there is no fallback as either user explicitly asked for
	 * the GuC or driver default option was to run with the GuC enabled.
	 */
	if (GEM_WARN_ON(ret == -EIO))
		ret = -EINVAL;

	dev_err(i915->drm.dev, "GuC initialization failed %d\n", ret);
	return ret;
}