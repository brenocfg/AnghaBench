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
struct intel_csr {int /*<<< orphan*/  work; int /*<<< orphan*/ * fw_path; scalar_t__ required_version; int /*<<< orphan*/  max_fw_size; } ;
struct drm_i915_private {struct intel_csr csr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dmc_firmware_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/ * BXT_CSR_PATH ; 
 scalar_t__ BXT_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  CNL_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/ * CNL_CSR_PATH ; 
 scalar_t__ CNL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  GEN12_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/  GLK_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/ * GLK_CSR_PATH ; 
 scalar_t__ GLK_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  HAS_CSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ICL_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/ * ICL_CSR_PATH ; 
 scalar_t__ ICL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  KBL_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/ * KBL_CSR_PATH ; 
 scalar_t__ KBL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  SKL_CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/ * SKL_CSR_PATH ; 
 scalar_t__ SKL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/ * TGL_CSR_PATH ; 
 scalar_t__ TGL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  csr_load_work_fn ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  intel_csr_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

void intel_csr_ucode_init(struct drm_i915_private *dev_priv)
{
	struct intel_csr *csr = &dev_priv->csr;

	INIT_WORK(&dev_priv->csr.work, csr_load_work_fn);

	if (!HAS_CSR(dev_priv))
		return;

	/*
	 * Obtain a runtime pm reference, until CSR is loaded, to avoid entering
	 * runtime-suspend.
	 *
	 * On error, we return with the rpm wakeref held to prevent runtime
	 * suspend as runtime suspend *requires* a working CSR for whatever
	 * reason.
	 */
	intel_csr_runtime_pm_get(dev_priv);

	if (INTEL_GEN(dev_priv) >= 12) {
		csr->fw_path = TGL_CSR_PATH;
		csr->required_version = TGL_CSR_VERSION_REQUIRED;
		/* Allow to load fw via parameter using the last known size */
		csr->max_fw_size = GEN12_CSR_MAX_FW_SIZE;
	} else if (IS_GEN(dev_priv, 11)) {
		csr->fw_path = ICL_CSR_PATH;
		csr->required_version = ICL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = ICL_CSR_MAX_FW_SIZE;
	} else if (IS_CANNONLAKE(dev_priv)) {
		csr->fw_path = CNL_CSR_PATH;
		csr->required_version = CNL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = CNL_CSR_MAX_FW_SIZE;
	} else if (IS_GEMINILAKE(dev_priv)) {
		csr->fw_path = GLK_CSR_PATH;
		csr->required_version = GLK_CSR_VERSION_REQUIRED;
		csr->max_fw_size = GLK_CSR_MAX_FW_SIZE;
	} else if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv)) {
		csr->fw_path = KBL_CSR_PATH;
		csr->required_version = KBL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = KBL_CSR_MAX_FW_SIZE;
	} else if (IS_SKYLAKE(dev_priv)) {
		csr->fw_path = SKL_CSR_PATH;
		csr->required_version = SKL_CSR_VERSION_REQUIRED;
		csr->max_fw_size = SKL_CSR_MAX_FW_SIZE;
	} else if (IS_BROXTON(dev_priv)) {
		csr->fw_path = BXT_CSR_PATH;
		csr->required_version = BXT_CSR_VERSION_REQUIRED;
		csr->max_fw_size = BXT_CSR_MAX_FW_SIZE;
	}

	if (i915_modparams.dmc_firmware_path) {
		if (strlen(i915_modparams.dmc_firmware_path) == 0) {
			csr->fw_path = NULL;
			DRM_INFO("Disabling CSR firmware and runtime PM\n");
			return;
		}

		csr->fw_path = i915_modparams.dmc_firmware_path;
		/* Bypass version check for firmware override. */
		csr->required_version = 0;
	}

	if (csr->fw_path == NULL) {
		DRM_DEBUG_KMS("No known CSR firmware for platform, disabling runtime PM\n");
		return;
	}

	DRM_DEBUG_KMS("Loading %s\n", csr->fw_path);
	schedule_work(&dev_priv->csr.work);
}