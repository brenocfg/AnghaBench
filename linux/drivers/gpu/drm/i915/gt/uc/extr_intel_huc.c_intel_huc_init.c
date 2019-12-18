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
struct intel_huc {int /*<<< orphan*/  fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_4__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* huc_to_gt (struct intel_huc*) ; 
 int intel_huc_rsa_data_create (struct intel_huc*) ; 
 int /*<<< orphan*/  intel_uc_fw_cleanup_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 
 int intel_uc_fw_init (int /*<<< orphan*/ *) ; 

int intel_huc_init(struct intel_huc *huc)
{
	struct drm_i915_private *i915 = huc_to_gt(huc)->i915;
	int err;

	err = intel_uc_fw_init(&huc->fw);
	if (err)
		goto out;

	/*
	 * HuC firmware image is outside GuC accessible range.
	 * Copy the RSA signature out of the image into
	 * a perma-pinned region set aside for it
	 */
	err = intel_huc_rsa_data_create(huc);
	if (err)
		goto out_fini;

	return 0;

out_fini:
	intel_uc_fw_fini(&huc->fw);
out:
	intel_uc_fw_cleanup_fetch(&huc->fw);
	DRM_DEV_DEBUG_DRIVER(i915->drm.dev, "failed with %d\n", err);
	return err;
}