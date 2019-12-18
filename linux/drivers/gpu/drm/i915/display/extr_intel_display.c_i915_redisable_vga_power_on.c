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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  i915_disable_vga (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_vgacntrl_reg (struct drm_i915_private*) ; 

void i915_redisable_vga_power_on(struct drm_i915_private *dev_priv)
{
	i915_reg_t vga_reg = i915_vgacntrl_reg(dev_priv);

	if (!(I915_READ(vga_reg) & VGA_DISP_DISABLE)) {
		DRM_DEBUG_KMS("Something enabled VGA plane, disabling it\n");
		i915_disable_vga(dev_priv);
	}
}