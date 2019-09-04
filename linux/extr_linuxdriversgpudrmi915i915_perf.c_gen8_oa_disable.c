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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GEN8_OACONTROL ; 
 int /*<<< orphan*/  GEN8_OA_COUNTER_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gen8_oa_disable(struct drm_i915_private *dev_priv)
{
	I915_WRITE(GEN8_OACONTROL, 0);
	if (intel_wait_for_register(dev_priv,
				    GEN8_OACONTROL, GEN8_OA_COUNTER_ENABLE, 0,
				    50))
		DRM_ERROR("wait for OA to be disabled timed out\n");
}