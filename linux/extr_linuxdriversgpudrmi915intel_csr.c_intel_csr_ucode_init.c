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
struct intel_csr {int /*<<< orphan*/  work; scalar_t__ fw_path; } ;
struct drm_i915_private {struct intel_csr csr; } ;
struct TYPE_2__ {scalar_t__ dmc_firmware_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HAS_CSR (struct drm_i915_private*) ; 
 scalar_t__ I915_CSR_BXT ; 
 scalar_t__ I915_CSR_CNL ; 
 scalar_t__ I915_CSR_GLK ; 
 scalar_t__ I915_CSR_KBL ; 
 scalar_t__ I915_CSR_SKL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  csr_load_work_fn ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void intel_csr_ucode_init(struct drm_i915_private *dev_priv)
{
	struct intel_csr *csr = &dev_priv->csr;

	INIT_WORK(&dev_priv->csr.work, csr_load_work_fn);

	if (!HAS_CSR(dev_priv))
		return;

	if (i915_modparams.dmc_firmware_path)
		csr->fw_path = i915_modparams.dmc_firmware_path;
	else if (IS_CANNONLAKE(dev_priv))
		csr->fw_path = I915_CSR_CNL;
	else if (IS_GEMINILAKE(dev_priv))
		csr->fw_path = I915_CSR_GLK;
	else if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv))
		csr->fw_path = I915_CSR_KBL;
	else if (IS_SKYLAKE(dev_priv))
		csr->fw_path = I915_CSR_SKL;
	else if (IS_BROXTON(dev_priv))
		csr->fw_path = I915_CSR_BXT;
	else {
		DRM_ERROR("Unexpected: no known CSR firmware for platform\n");
		return;
	}

	DRM_DEBUG_KMS("Loading %s\n", csr->fw_path);

	/*
	 * Obtain a runtime pm reference, until CSR is loaded,
	 * to avoid entering runtime-suspend.
	 */
	intel_display_power_get(dev_priv, POWER_DOMAIN_INIT);

	schedule_work(&dev_priv->csr.work);
}