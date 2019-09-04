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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSPFW3 ; 
 int /*<<< orphan*/  FW_BLC_SELF ; 
 int FW_BLC_SELF_EN ; 
 int /*<<< orphan*/  FW_BLC_SELF_VLV ; 
 int FW_CSPWRDWNEN ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INSTPM ; 
 int INSTPM_SELF_EN ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_I915GM (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_I965GM (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int PINEVIEW_SELF_REFRESH_EN ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_DISABLE (int) ; 
 int _MASKED_BIT_ENABLE (int) ; 
 int /*<<< orphan*/  enableddisabled (int) ; 
 int /*<<< orphan*/  trace_intel_memory_cxsr (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static bool _intel_set_memory_cxsr(struct drm_i915_private *dev_priv, bool enable)
{
	bool was_enabled;
	u32 val;

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		was_enabled = I915_READ(FW_BLC_SELF_VLV) & FW_CSPWRDWNEN;
		I915_WRITE(FW_BLC_SELF_VLV, enable ? FW_CSPWRDWNEN : 0);
		POSTING_READ(FW_BLC_SELF_VLV);
	} else if (IS_G4X(dev_priv) || IS_I965GM(dev_priv)) {
		was_enabled = I915_READ(FW_BLC_SELF) & FW_BLC_SELF_EN;
		I915_WRITE(FW_BLC_SELF, enable ? FW_BLC_SELF_EN : 0);
		POSTING_READ(FW_BLC_SELF);
	} else if (IS_PINEVIEW(dev_priv)) {
		val = I915_READ(DSPFW3);
		was_enabled = val & PINEVIEW_SELF_REFRESH_EN;
		if (enable)
			val |= PINEVIEW_SELF_REFRESH_EN;
		else
			val &= ~PINEVIEW_SELF_REFRESH_EN;
		I915_WRITE(DSPFW3, val);
		POSTING_READ(DSPFW3);
	} else if (IS_I945G(dev_priv) || IS_I945GM(dev_priv)) {
		was_enabled = I915_READ(FW_BLC_SELF) & FW_BLC_SELF_EN;
		val = enable ? _MASKED_BIT_ENABLE(FW_BLC_SELF_EN) :
			       _MASKED_BIT_DISABLE(FW_BLC_SELF_EN);
		I915_WRITE(FW_BLC_SELF, val);
		POSTING_READ(FW_BLC_SELF);
	} else if (IS_I915GM(dev_priv)) {
		/*
		 * FIXME can't find a bit like this for 915G, and
		 * and yet it does have the related watermark in
		 * FW_BLC_SELF. What's going on?
		 */
		was_enabled = I915_READ(INSTPM) & INSTPM_SELF_EN;
		val = enable ? _MASKED_BIT_ENABLE(INSTPM_SELF_EN) :
			       _MASKED_BIT_DISABLE(INSTPM_SELF_EN);
		I915_WRITE(INSTPM, val);
		POSTING_READ(INSTPM);
	} else {
		return false;
	}

	trace_intel_memory_cxsr(dev_priv, was_enabled, enable);

	DRM_DEBUG_KMS("memory self-refresh is %s (was %s)\n",
		      enableddisabled(enable),
		      enableddisabled(was_enabled));

	return was_enabled;
}