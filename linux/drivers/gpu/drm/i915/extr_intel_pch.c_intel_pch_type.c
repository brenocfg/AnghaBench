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
typedef  enum intel_pch { ____Placeholder_intel_pch } intel_pch ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
#define  INTEL_PCH_CMP2_DEVICE_ID_TYPE 145 
#define  INTEL_PCH_CMP_DEVICE_ID_TYPE 144 
#define  INTEL_PCH_CNP_DEVICE_ID_TYPE 143 
#define  INTEL_PCH_CNP_LP_DEVICE_ID_TYPE 142 
#define  INTEL_PCH_CPT_DEVICE_ID_TYPE 141 
#define  INTEL_PCH_IBX_DEVICE_ID_TYPE 140 
#define  INTEL_PCH_ICP_DEVICE_ID_TYPE 139 
#define  INTEL_PCH_KBP_DEVICE_ID_TYPE 138 
#define  INTEL_PCH_LPT_DEVICE_ID_TYPE 137 
#define  INTEL_PCH_LPT_LP_DEVICE_ID_TYPE 136 
#define  INTEL_PCH_MCC2_DEVICE_ID_TYPE 135 
#define  INTEL_PCH_MCC_DEVICE_ID_TYPE 134 
#define  INTEL_PCH_PPT_DEVICE_ID_TYPE 133 
#define  INTEL_PCH_SPT_DEVICE_ID_TYPE 132 
#define  INTEL_PCH_SPT_LP_DEVICE_ID_TYPE 131 
#define  INTEL_PCH_TGP_DEVICE_ID_TYPE 130 
#define  INTEL_PCH_WPT_DEVICE_ID_TYPE 129 
#define  INTEL_PCH_WPT_LP_DEVICE_ID_TYPE 128 
 int /*<<< orphan*/  IS_BDW_ULT (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_BROADWELL (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_CANNONLAKE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_COFFEELAKE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_ELKHARTLAKE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_GEN (struct drm_i915_private const*,int) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_HSW_ULT (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_ICELAKE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_IVYBRIDGE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_KABYLAKE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_SKYLAKE (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  IS_TIGERLAKE (struct drm_i915_private const*) ; 
 int PCH_CNP ; 
 int PCH_CPT ; 
 int PCH_IBX ; 
 int PCH_ICP ; 
 int PCH_LPT ; 
 int PCH_MCC ; 
 int PCH_NONE ; 
 int PCH_SPT ; 
 int PCH_TGP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static enum intel_pch
intel_pch_type(const struct drm_i915_private *dev_priv, unsigned short id)
{
	switch (id) {
	case INTEL_PCH_IBX_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Ibex Peak PCH\n");
		WARN_ON(!IS_GEN(dev_priv, 5));
		return PCH_IBX;
	case INTEL_PCH_CPT_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found CougarPoint PCH\n");
		WARN_ON(!IS_GEN(dev_priv, 6) && !IS_IVYBRIDGE(dev_priv));
		return PCH_CPT;
	case INTEL_PCH_PPT_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found PantherPoint PCH\n");
		WARN_ON(!IS_GEN(dev_priv, 6) && !IS_IVYBRIDGE(dev_priv));
		/* PantherPoint is CPT compatible */
		return PCH_CPT;
	case INTEL_PCH_LPT_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found LynxPoint PCH\n");
		WARN_ON(!IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		WARN_ON(IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv));
		return PCH_LPT;
	case INTEL_PCH_LPT_LP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found LynxPoint LP PCH\n");
		WARN_ON(!IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		WARN_ON(!IS_HSW_ULT(dev_priv) && !IS_BDW_ULT(dev_priv));
		return PCH_LPT;
	case INTEL_PCH_WPT_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found WildcatPoint PCH\n");
		WARN_ON(!IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		WARN_ON(IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv));
		/* WildcatPoint is LPT compatible */
		return PCH_LPT;
	case INTEL_PCH_WPT_LP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found WildcatPoint LP PCH\n");
		WARN_ON(!IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv));
		WARN_ON(!IS_HSW_ULT(dev_priv) && !IS_BDW_ULT(dev_priv));
		/* WildcatPoint is LPT compatible */
		return PCH_LPT;
	case INTEL_PCH_SPT_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found SunrisePoint PCH\n");
		WARN_ON(!IS_SKYLAKE(dev_priv) && !IS_KABYLAKE(dev_priv));
		return PCH_SPT;
	case INTEL_PCH_SPT_LP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found SunrisePoint LP PCH\n");
		WARN_ON(!IS_SKYLAKE(dev_priv) && !IS_KABYLAKE(dev_priv));
		return PCH_SPT;
	case INTEL_PCH_KBP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Kaby Lake PCH (KBP)\n");
		WARN_ON(!IS_SKYLAKE(dev_priv) && !IS_KABYLAKE(dev_priv) &&
			!IS_COFFEELAKE(dev_priv));
		/* KBP is SPT compatible */
		return PCH_SPT;
	case INTEL_PCH_CNP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Cannon Lake PCH (CNP)\n");
		WARN_ON(!IS_CANNONLAKE(dev_priv) && !IS_COFFEELAKE(dev_priv));
		return PCH_CNP;
	case INTEL_PCH_CNP_LP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Cannon Lake LP PCH (CNP-LP)\n");
		WARN_ON(!IS_CANNONLAKE(dev_priv) && !IS_COFFEELAKE(dev_priv));
		return PCH_CNP;
	case INTEL_PCH_CMP_DEVICE_ID_TYPE:
	case INTEL_PCH_CMP2_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Comet Lake PCH (CMP)\n");
		WARN_ON(!IS_COFFEELAKE(dev_priv));
		/* CometPoint is CNP Compatible */
		return PCH_CNP;
	case INTEL_PCH_ICP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Ice Lake PCH\n");
		WARN_ON(!IS_ICELAKE(dev_priv));
		return PCH_ICP;
	case INTEL_PCH_MCC_DEVICE_ID_TYPE:
	case INTEL_PCH_MCC2_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Mule Creek Canyon PCH\n");
		WARN_ON(!IS_ELKHARTLAKE(dev_priv));
		return PCH_MCC;
	case INTEL_PCH_TGP_DEVICE_ID_TYPE:
		DRM_DEBUG_KMS("Found Tiger Lake LP PCH\n");
		WARN_ON(!IS_TIGERLAKE(dev_priv));
		return PCH_TGP;
	default:
		return PCH_NONE;
	}
}