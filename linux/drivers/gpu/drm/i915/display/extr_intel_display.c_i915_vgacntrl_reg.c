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
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_VGACNTRL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  VGACNTRL ; 
 int /*<<< orphan*/  VLV_VGACNTRL ; 

__attribute__((used)) static i915_reg_t i915_vgacntrl_reg(struct drm_i915_private *dev_priv)
{
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		return VLV_VGACNTRL;
	else if (INTEL_GEN(dev_priv) >= 5)
		return CPU_VGACNTRL;
	else
		return VGACNTRL;
}