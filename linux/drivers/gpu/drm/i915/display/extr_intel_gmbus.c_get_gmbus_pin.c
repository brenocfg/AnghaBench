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
struct gmbus_pin {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CNP (struct drm_i915_private*) ; 
 scalar_t__ INTEL_PCH_TYPE (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ PCH_ICP ; 
 struct gmbus_pin const* gmbus_pins ; 
 struct gmbus_pin const* gmbus_pins_bdw ; 
 struct gmbus_pin const* gmbus_pins_bxt ; 
 struct gmbus_pin const* gmbus_pins_cnp ; 
 struct gmbus_pin const* gmbus_pins_icp ; 
 struct gmbus_pin const* gmbus_pins_skl ; 

__attribute__((used)) static const struct gmbus_pin *get_gmbus_pin(struct drm_i915_private *dev_priv,
					     unsigned int pin)
{
	if (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		return &gmbus_pins_icp[pin];
	else if (HAS_PCH_CNP(dev_priv))
		return &gmbus_pins_cnp[pin];
	else if (IS_GEN9_LP(dev_priv))
		return &gmbus_pins_bxt[pin];
	else if (IS_GEN9_BC(dev_priv))
		return &gmbus_pins_skl[pin];
	else if (IS_BROADWELL(dev_priv))
		return &gmbus_pins_bdw[pin];
	else
		return &gmbus_pins[pin];
}