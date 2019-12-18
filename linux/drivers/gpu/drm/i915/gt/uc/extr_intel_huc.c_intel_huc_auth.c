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
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct intel_huc {int /*<<< orphan*/  fw; TYPE_2__ status; int /*<<< orphan*/  rsa_data; } ;
struct intel_guc {int dummy; } ;
struct TYPE_3__ {struct intel_guc guc; } ;
struct intel_gt {int /*<<< orphan*/  i915; int /*<<< orphan*/  uncore; TYPE_1__ uc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_FAIL ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_RUNNING ; 
 int __intel_wait_for_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct intel_gt* huc_to_gt (struct intel_huc*) ; 
 int i915_inject_load_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_probe_error (int /*<<< orphan*/ ,char*,int) ; 
 int intel_guc_auth_huc (struct intel_guc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_guc_ggtt_offset (struct intel_guc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_huc_is_authenticated (struct intel_huc*) ; 
 int /*<<< orphan*/  intel_uc_fw_change_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_is_loaded (int /*<<< orphan*/ *) ; 

int intel_huc_auth(struct intel_huc *huc)
{
	struct intel_gt *gt = huc_to_gt(huc);
	struct intel_guc *guc = &gt->uc.guc;
	int ret;

	GEM_BUG_ON(intel_huc_is_authenticated(huc));

	if (!intel_uc_fw_is_loaded(&huc->fw))
		return -ENOEXEC;

	ret = i915_inject_load_error(gt->i915, -ENXIO);
	if (ret)
		goto fail;

	ret = intel_guc_auth_huc(guc,
				 intel_guc_ggtt_offset(guc, huc->rsa_data));
	if (ret) {
		DRM_ERROR("HuC: GuC did not ack Auth request %d\n", ret);
		goto fail;
	}

	/* Check authentication status, it should be done by now */
	ret = __intel_wait_for_register(gt->uncore,
					huc->status.reg,
					huc->status.mask,
					huc->status.value,
					2, 50, NULL);
	if (ret) {
		DRM_ERROR("HuC: Firmware not verified %d\n", ret);
		goto fail;
	}

	intel_uc_fw_change_status(&huc->fw, INTEL_UC_FIRMWARE_RUNNING);
	return 0;

fail:
	i915_probe_error(gt->i915, "HuC: Authentication failed %d\n", ret);
	intel_uc_fw_change_status(&huc->fw, INTEL_UC_FIRMWARE_FAIL);
	return ret;
}