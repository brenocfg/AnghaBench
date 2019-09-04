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
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ intel_has_gpu_reset (struct drm_i915_private*) ; 

__attribute__((used)) static bool gpu_reset_clobbers_display(struct drm_i915_private *dev_priv)
{
	return intel_has_gpu_reset(dev_priv) &&
		INTEL_GEN(dev_priv) < 5 && !IS_G4X(dev_priv);
}