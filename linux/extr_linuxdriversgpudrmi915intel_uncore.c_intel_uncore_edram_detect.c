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
struct drm_i915_private {scalar_t__ edram_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 scalar_t__ HAS_EDRAM (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HSW_EDRAM_CAP ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_uncore_edram_size (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_uncore_edram_detect(struct drm_i915_private *dev_priv)
{
	if (IS_HASWELL(dev_priv) ||
	    IS_BROADWELL(dev_priv) ||
	    INTEL_GEN(dev_priv) >= 9) {
		dev_priv->edram_cap = __raw_i915_read32(dev_priv,
							HSW_EDRAM_CAP);

		/* NB: We can't write IDICR yet because we do not have gt funcs
		 * set up */
	} else {
		dev_priv->edram_cap = 0;
	}

	if (HAS_EDRAM(dev_priv))
		DRM_INFO("Found %lluMB of eDRAM\n",
			 intel_uncore_edram_size(dev_priv) / (1024 * 1024));
}