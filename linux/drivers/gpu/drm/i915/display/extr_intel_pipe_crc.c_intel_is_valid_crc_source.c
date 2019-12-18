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
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int i8xx_crc_source_valid (struct drm_i915_private*,int const) ; 
 int i9xx_crc_source_valid (struct drm_i915_private*,int const) ; 
 int ilk_crc_source_valid (struct drm_i915_private*,int const) ; 
 int ivb_crc_source_valid (struct drm_i915_private*,int const) ; 
 int skl_crc_source_valid (struct drm_i915_private*,int const) ; 
 int vlv_crc_source_valid (struct drm_i915_private*,int const) ; 

__attribute__((used)) static int
intel_is_valid_crc_source(struct drm_i915_private *dev_priv,
			  const enum intel_pipe_crc_source source)
{
	if (IS_GEN(dev_priv, 2))
		return i8xx_crc_source_valid(dev_priv, source);
	else if (INTEL_GEN(dev_priv) < 5)
		return i9xx_crc_source_valid(dev_priv, source);
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		return vlv_crc_source_valid(dev_priv, source);
	else if (IS_GEN_RANGE(dev_priv, 5, 6))
		return ilk_crc_source_valid(dev_priv, source);
	else if (INTEL_GEN(dev_priv) < 9)
		return ivb_crc_source_valid(dev_priv, source);
	else
		return skl_crc_source_valid(dev_priv, source);
}