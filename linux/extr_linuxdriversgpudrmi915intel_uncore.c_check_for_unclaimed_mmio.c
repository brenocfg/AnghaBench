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
 scalar_t__ HAS_FPGA_DBG_UNCLAIMED (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int fpga_check_for_unclaimed_mmio (struct drm_i915_private*) ; 
 int gen6_check_for_fifo_debug (struct drm_i915_private*) ; 
 int vlv_check_for_unclaimed_mmio (struct drm_i915_private*) ; 

__attribute__((used)) static bool
check_for_unclaimed_mmio(struct drm_i915_private *dev_priv)
{
	bool ret = false;

	if (HAS_FPGA_DBG_UNCLAIMED(dev_priv))
		ret |= fpga_check_for_unclaimed_mmio(dev_priv);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret |= vlv_check_for_unclaimed_mmio(dev_priv);

	if (IS_GEN6(dev_priv) || IS_GEN7(dev_priv))
		ret |= gen6_check_for_fifo_debug(dev_priv);

	return ret;
}