#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int base; int size; } ;
struct intel_wopcm {int size; TYPE_3__ guc; } ;
struct TYPE_5__ {int /*<<< orphan*/  fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw; } ;
struct drm_i915_private {TYPE_2__ huc; TYPE_1__ guc; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int E2BIG ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GUC_WOPCM_OFFSET_ALIGNMENT ; 
 int GUC_WOPCM_RESERVED ; 
 int GUC_WOPCM_SIZE_MASK ; 
 int GUC_WOPCM_STACK_RESERVED ; 
 scalar_t__ WOPCM_RESERVED_SIZE ; 
 int check_hw_restriction (struct drm_i915_private*,int,int,int) ; 
 int context_reserved_size (struct drm_i915_private*) ; 
 int intel_uc_fw_get_upload_size (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* wopcm_to_i915 (struct intel_wopcm*) ; 

int intel_wopcm_init(struct intel_wopcm *wopcm)
{
	struct drm_i915_private *i915 = wopcm_to_i915(wopcm);
	u32 guc_fw_size = intel_uc_fw_get_upload_size(&i915->guc.fw);
	u32 huc_fw_size = intel_uc_fw_get_upload_size(&i915->huc.fw);
	u32 ctx_rsvd = context_reserved_size(i915);
	u32 guc_wopcm_base;
	u32 guc_wopcm_size;
	u32 guc_wopcm_rsvd;
	int err;

	GEM_BUG_ON(!wopcm->size);

	if (guc_fw_size >= wopcm->size) {
		DRM_ERROR("GuC FW (%uKiB) is too big to fit in WOPCM.",
			  guc_fw_size / 1024);
		return -E2BIG;
	}

	if (huc_fw_size >= wopcm->size) {
		DRM_ERROR("HuC FW (%uKiB) is too big to fit in WOPCM.",
			  huc_fw_size / 1024);
		return -E2BIG;
	}

	guc_wopcm_base = ALIGN(huc_fw_size + WOPCM_RESERVED_SIZE,
			       GUC_WOPCM_OFFSET_ALIGNMENT);
	if ((guc_wopcm_base + ctx_rsvd) >= wopcm->size) {
		DRM_ERROR("GuC WOPCM base (%uKiB) is too big.\n",
			  guc_wopcm_base / 1024);
		return -E2BIG;
	}

	guc_wopcm_size = wopcm->size - guc_wopcm_base - ctx_rsvd;
	guc_wopcm_size &= GUC_WOPCM_SIZE_MASK;

	DRM_DEBUG_DRIVER("Calculated GuC WOPCM Region: [%uKiB, %uKiB)\n",
			 guc_wopcm_base / 1024, guc_wopcm_size / 1024);

	guc_wopcm_rsvd = GUC_WOPCM_RESERVED + GUC_WOPCM_STACK_RESERVED;
	if ((guc_fw_size + guc_wopcm_rsvd) > guc_wopcm_size) {
		DRM_ERROR("Need %uKiB WOPCM for GuC, %uKiB available.\n",
			  (guc_fw_size + guc_wopcm_rsvd) / 1024,
			  guc_wopcm_size / 1024);
		return -E2BIG;
	}

	err = check_hw_restriction(i915, guc_wopcm_base, guc_wopcm_size,
				   huc_fw_size);
	if (err)
		return err;

	wopcm->guc.base = guc_wopcm_base;
	wopcm->guc.size = guc_wopcm_size;

	return 0;
}