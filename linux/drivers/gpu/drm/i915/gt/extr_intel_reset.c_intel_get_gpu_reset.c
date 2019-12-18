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
typedef  int /*<<< orphan*/ * reset_func ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_G33 (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/ * g33_do_reset ; 
 int /*<<< orphan*/ * g4x_do_reset ; 
 int /*<<< orphan*/ * gen6_reset_engines ; 
 int /*<<< orphan*/ * gen8_reset_engines ; 
 int /*<<< orphan*/ * i915_do_reset ; 
 int /*<<< orphan*/ * ironlake_do_reset ; 

__attribute__((used)) static reset_func intel_get_gpu_reset(struct drm_i915_private *i915)
{
	if (INTEL_GEN(i915) >= 8)
		return gen8_reset_engines;
	else if (INTEL_GEN(i915) >= 6)
		return gen6_reset_engines;
	else if (INTEL_GEN(i915) >= 5)
		return ironlake_do_reset;
	else if (IS_G4X(i915))
		return g4x_do_reset;
	else if (IS_G33(i915) || IS_PINEVIEW(i915))
		return g33_do_reset;
	else if (INTEL_GEN(i915) >= 3)
		return i915_do_reset;
	else
		return NULL;
}