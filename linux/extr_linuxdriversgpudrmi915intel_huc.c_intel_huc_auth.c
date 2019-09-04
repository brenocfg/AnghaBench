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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ load_status; scalar_t__ rsa_offset; int /*<<< orphan*/  obj; } ;
struct intel_huc {TYPE_1__ fw; } ;
struct intel_guc {int ggtt_pin_bias; } ;
struct i915_vma {int dummy; } ;
struct drm_i915_private {struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  HUC_FW_VERIFIED ; 
 int /*<<< orphan*/  HUC_STATUS2 ; 
 scalar_t__ INTEL_UC_FIRMWARE_FAIL ; 
 scalar_t__ INTEL_UC_FIRMWARE_SUCCESS ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PIN_OFFSET_BIAS ; 
 int PTR_ERR (struct i915_vma*) ; 
 int __intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 struct drm_i915_private* huc_to_i915 (struct intel_huc*) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int intel_guc_auth_huc (struct intel_guc*,scalar_t__) ; 
 scalar_t__ intel_guc_ggtt_offset (struct intel_guc*,struct i915_vma*) ; 

int intel_huc_auth(struct intel_huc *huc)
{
	struct drm_i915_private *i915 = huc_to_i915(huc);
	struct intel_guc *guc = &i915->guc;
	struct i915_vma *vma;
	u32 status;
	int ret;

	if (huc->fw.load_status != INTEL_UC_FIRMWARE_SUCCESS)
		return -ENOEXEC;

	vma = i915_gem_object_ggtt_pin(huc->fw.obj, NULL, 0, 0,
				       PIN_OFFSET_BIAS | guc->ggtt_pin_bias);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		DRM_ERROR("HuC: Failed to pin huc fw object %d\n", ret);
		goto fail;
	}

	ret = intel_guc_auth_huc(guc,
				 intel_guc_ggtt_offset(guc, vma) +
				 huc->fw.rsa_offset);
	if (ret) {
		DRM_ERROR("HuC: GuC did not ack Auth request %d\n", ret);
		goto fail_unpin;
	}

	/* Check authentication status, it should be done by now */
	ret = __intel_wait_for_register(i915,
					HUC_STATUS2,
					HUC_FW_VERIFIED,
					HUC_FW_VERIFIED,
					2, 50, &status);
	if (ret) {
		DRM_ERROR("HuC: Firmware not verified %#x\n", status);
		goto fail_unpin;
	}

	i915_vma_unpin(vma);
	return 0;

fail_unpin:
	i915_vma_unpin(vma);
fail:
	huc->fw.load_status = INTEL_UC_FIRMWARE_FAIL;

	DRM_ERROR("HuC: Authentication failed %d\n", ret);
	return ret;
}