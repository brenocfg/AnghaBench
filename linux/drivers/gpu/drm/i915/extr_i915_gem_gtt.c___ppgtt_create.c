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
struct i915_ppgtt {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct i915_ppgtt* gen6_ppgtt_create (struct drm_i915_private*) ; 
 struct i915_ppgtt* gen8_ppgtt_create (struct drm_i915_private*) ; 

__attribute__((used)) static struct i915_ppgtt *
__ppgtt_create(struct drm_i915_private *i915)
{
	if (INTEL_GEN(i915) < 8)
		return gen6_ppgtt_create(i915);
	else
		return gen8_ppgtt_create(i915);
}