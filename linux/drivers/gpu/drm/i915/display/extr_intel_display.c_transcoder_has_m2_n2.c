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
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int TRANSCODER_EDP ; 

__attribute__((used)) static bool transcoder_has_m2_n2(struct drm_i915_private *dev_priv,
				 enum transcoder transcoder)
{
	if (IS_HASWELL(dev_priv))
		return transcoder == TRANSCODER_EDP;

	/*
	 * Strictly speaking some registers are available before
	 * gen7, but we only support DRRS on gen7+
	 */
	return IS_GEN(dev_priv, 7) || IS_CHERRYVIEW(dev_priv);
}