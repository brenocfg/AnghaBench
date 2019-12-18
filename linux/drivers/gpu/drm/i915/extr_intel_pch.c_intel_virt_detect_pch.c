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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 unsigned short INTEL_PCH_CNP_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_CPT_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_IBX_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_ICP_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_LPT_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_LPT_LP_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_MCC_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_SPT_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_TGP_DEVICE_ID_TYPE ; 
 scalar_t__ IS_BDW_ULT (struct drm_i915_private const*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private const*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private const*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private const*) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private const*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private const*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private const*) ; 
 scalar_t__ IS_HSW_ULT (struct drm_i915_private const*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private const*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private const*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private const*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private const*) ; 
 scalar_t__ IS_TIGERLAKE (struct drm_i915_private const*) ; 

__attribute__((used)) static unsigned short
intel_virt_detect_pch(const struct drm_i915_private *dev_priv)
{
	unsigned short id = 0;

	/*
	 * In a virtualized passthrough environment we can be in a
	 * setup where the ISA bridge is not able to be passed through.
	 * In this case, a south bridge can be emulated and we have to
	 * make an educated guess as to which PCH is really there.
	 */

	if (IS_TIGERLAKE(dev_priv))
		id = INTEL_PCH_TGP_DEVICE_ID_TYPE;
	else if (IS_ELKHARTLAKE(dev_priv))
		id = INTEL_PCH_MCC_DEVICE_ID_TYPE;
	else if (IS_ICELAKE(dev_priv))
		id = INTEL_PCH_ICP_DEVICE_ID_TYPE;
	else if (IS_CANNONLAKE(dev_priv) || IS_COFFEELAKE(dev_priv))
		id = INTEL_PCH_CNP_DEVICE_ID_TYPE;
	else if (IS_KABYLAKE(dev_priv) || IS_SKYLAKE(dev_priv))
		id = INTEL_PCH_SPT_DEVICE_ID_TYPE;
	else if (IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv))
		id = INTEL_PCH_LPT_LP_DEVICE_ID_TYPE;
	else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		id = INTEL_PCH_LPT_DEVICE_ID_TYPE;
	else if (IS_GEN(dev_priv, 6) || IS_IVYBRIDGE(dev_priv))
		id = INTEL_PCH_CPT_DEVICE_ID_TYPE;
	else if (IS_GEN(dev_priv, 5))
		id = INTEL_PCH_IBX_DEVICE_ID_TYPE;

	if (id)
		DRM_DEBUG_KMS("Assuming PCH ID %04x\n", id);
	else
		DRM_DEBUG_KMS("Assuming no PCH\n");

	return id;
}