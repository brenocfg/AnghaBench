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
struct TYPE_2__ {scalar_t__ count; } ;
struct drm_i915_private {TYPE_1__ workarounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int bdw_ctx_workarounds_init (struct drm_i915_private*) ; 
 int bxt_ctx_workarounds_init (struct drm_i915_private*) ; 
 int cfl_ctx_workarounds_init (struct drm_i915_private*) ; 
 int chv_ctx_workarounds_init (struct drm_i915_private*) ; 
 int cnl_ctx_workarounds_init (struct drm_i915_private*) ; 
 int glk_ctx_workarounds_init (struct drm_i915_private*) ; 
 int icl_ctx_workarounds_init (struct drm_i915_private*) ; 
 int kbl_ctx_workarounds_init (struct drm_i915_private*) ; 
 int skl_ctx_workarounds_init (struct drm_i915_private*) ; 

int intel_ctx_workarounds_init(struct drm_i915_private *dev_priv)
{
	int err = 0;

	dev_priv->workarounds.count = 0;

	if (INTEL_GEN(dev_priv) < 8)
		err = 0;
	else if (IS_BROADWELL(dev_priv))
		err = bdw_ctx_workarounds_init(dev_priv);
	else if (IS_CHERRYVIEW(dev_priv))
		err = chv_ctx_workarounds_init(dev_priv);
	else if (IS_SKYLAKE(dev_priv))
		err = skl_ctx_workarounds_init(dev_priv);
	else if (IS_BROXTON(dev_priv))
		err = bxt_ctx_workarounds_init(dev_priv);
	else if (IS_KABYLAKE(dev_priv))
		err = kbl_ctx_workarounds_init(dev_priv);
	else if (IS_GEMINILAKE(dev_priv))
		err = glk_ctx_workarounds_init(dev_priv);
	else if (IS_COFFEELAKE(dev_priv))
		err = cfl_ctx_workarounds_init(dev_priv);
	else if (IS_CANNONLAKE(dev_priv))
		err = cnl_ctx_workarounds_init(dev_priv);
	else if (IS_ICELAKE(dev_priv))
		err = icl_ctx_workarounds_init(dev_priv);
	else
		MISSING_CASE(INTEL_GEN(dev_priv));
	if (err)
		return err;

	DRM_DEBUG_DRIVER("Number of context specific w/a: %d\n",
			 dev_priv->workarounds.count);
	return 0;
}