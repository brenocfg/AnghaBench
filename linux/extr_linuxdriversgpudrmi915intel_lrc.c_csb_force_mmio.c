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
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_vgpu_has_hwsp_emulation (struct drm_i915_private*) ; 

__attribute__((used)) static bool csb_force_mmio(struct drm_i915_private *i915)
{
	/* Older GVT emulation depends upon intercepting CSB mmio */
	return intel_vgpu_active(i915) && !intel_vgpu_has_hwsp_emulation(i915);
}