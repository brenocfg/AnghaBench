#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_uc_fw {int path; scalar_t__ fetch_status; int /*<<< orphan*/  type; scalar_t__ load_status; int /*<<< orphan*/  minor_ver_found; int /*<<< orphan*/  major_ver_found; TYPE_4__* obj; } ;
typedef  struct i915_vma i915_vma ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_2__ base; } ;
struct TYPE_6__ {int ggtt_pin_bias; } ;
struct TYPE_8__ {TYPE_1__ guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_WARN (char*,int /*<<< orphan*/ ,int,int) ; 
 int ENOEXEC ; 
 scalar_t__ INTEL_UC_FIRMWARE_FAIL ; 
 scalar_t__ INTEL_UC_FIRMWARE_PENDING ; 
 scalar_t__ INTEL_UC_FIRMWARE_SUCCESS ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PIN_OFFSET_BIAS ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i915_gem_object_set_to_gtt_domain (TYPE_4__*,int) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int intel_uc_fw_status_repr (scalar_t__) ; 
 int /*<<< orphan*/  intel_uc_fw_type_repr (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_i915 (int /*<<< orphan*/ ) ; 

int intel_uc_fw_upload(struct intel_uc_fw *uc_fw,
		       int (*xfer)(struct intel_uc_fw *uc_fw,
				   struct i915_vma *vma))
{
	struct i915_vma *vma;
	u32 ggtt_pin_bias;
	int err;

	DRM_DEBUG_DRIVER("%s fw load %s\n",
			 intel_uc_fw_type_repr(uc_fw->type), uc_fw->path);

	if (uc_fw->fetch_status != INTEL_UC_FIRMWARE_SUCCESS)
		return -ENOEXEC;

	uc_fw->load_status = INTEL_UC_FIRMWARE_PENDING;
	DRM_DEBUG_DRIVER("%s fw load %s\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 intel_uc_fw_status_repr(uc_fw->load_status));

	/* Pin object with firmware */
	err = i915_gem_object_set_to_gtt_domain(uc_fw->obj, false);
	if (err) {
		DRM_DEBUG_DRIVER("%s fw set-domain err=%d\n",
				 intel_uc_fw_type_repr(uc_fw->type), err);
		goto fail;
	}

	ggtt_pin_bias = to_i915(uc_fw->obj->base.dev)->guc.ggtt_pin_bias;
	vma = i915_gem_object_ggtt_pin(uc_fw->obj, NULL, 0, 0,
				       PIN_OFFSET_BIAS | ggtt_pin_bias);
	if (IS_ERR(vma)) {
		err = PTR_ERR(vma);
		DRM_DEBUG_DRIVER("%s fw ggtt-pin err=%d\n",
				 intel_uc_fw_type_repr(uc_fw->type), err);
		goto fail;
	}

	/* Call custom loader */
	err = xfer(uc_fw, vma);

	/*
	 * We keep the object pages for reuse during resume. But we can unpin it
	 * now that DMA has completed, so it doesn't continue to take up space.
	 */
	i915_vma_unpin(vma);

	if (err)
		goto fail;

	uc_fw->load_status = INTEL_UC_FIRMWARE_SUCCESS;
	DRM_DEBUG_DRIVER("%s fw load %s\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 intel_uc_fw_status_repr(uc_fw->load_status));

	DRM_INFO("%s: Loaded firmware %s (version %u.%u)\n",
		 intel_uc_fw_type_repr(uc_fw->type),
		 uc_fw->path,
		 uc_fw->major_ver_found, uc_fw->minor_ver_found);

	return 0;

fail:
	uc_fw->load_status = INTEL_UC_FIRMWARE_FAIL;
	DRM_DEBUG_DRIVER("%s fw load %s\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 intel_uc_fw_status_repr(uc_fw->load_status));

	DRM_WARN("%s: Failed to load firmware %s (error %d)\n",
		 intel_uc_fw_type_repr(uc_fw->type), uc_fw->path, err);

	return err;
}