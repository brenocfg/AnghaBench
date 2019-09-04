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
 int DFR_DISABLE ; 
 int /*<<< orphan*/  GEN10_DFR_RATIO_EN_AND_CHICKEN ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icl_init_clock_gating(struct drm_i915_private *dev_priv)
{
	/* This is not an Wa. Enable to reduce Sampler power */
	I915_WRITE(GEN10_DFR_RATIO_EN_AND_CHICKEN,
		   I915_READ(GEN10_DFR_RATIO_EN_AND_CHICKEN) & ~DFR_DISABLE);
}