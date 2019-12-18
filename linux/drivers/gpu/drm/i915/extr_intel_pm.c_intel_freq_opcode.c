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
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int GEN9_FREQ_SCALER ; 
 int /*<<< orphan*/  GT_FREQUENCY_MULTIPLIER ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int byt_freq_opcode (struct drm_i915_private*,int) ; 
 int chv_freq_opcode (struct drm_i915_private*,int) ; 

int intel_freq_opcode(struct drm_i915_private *dev_priv, int val)
{
	if (INTEL_GEN(dev_priv) >= 9)
		return DIV_ROUND_CLOSEST(val * GEN9_FREQ_SCALER,
					 GT_FREQUENCY_MULTIPLIER);
	else if (IS_CHERRYVIEW(dev_priv))
		return chv_freq_opcode(dev_priv, val);
	else if (IS_VALLEYVIEW(dev_priv))
		return byt_freq_opcode(dev_priv, val);
	else
		return DIV_ROUND_CLOSEST(val, GT_FREQUENCY_MULTIPLIER);
}