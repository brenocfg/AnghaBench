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
 int /*<<< orphan*/  FF_SLICE_CS_CHICKEN2 ; 
 int GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 int /*<<< orphan*/  GEN9_POOLED_EU_LOAD_BALANCING_FIX_DISABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen9_gt_workarounds_apply (struct drm_i915_private*) ; 

__attribute__((used)) static void bxt_gt_workarounds_apply(struct drm_i915_private *dev_priv)
{
	gen9_gt_workarounds_apply(dev_priv);

	/* WaDisablePooledEuLoadBalancingFix:bxt */
	I915_WRITE(FF_SLICE_CS_CHICKEN2,
		   _MASKED_BIT_ENABLE(GEN9_POOLED_EU_LOAD_BALANCING_FIX_DISABLE));

	/* WaInPlaceDecompressionHang:bxt */
	I915_WRITE(GEN9_GAMT_ECO_REG_RW_IA,
		   I915_READ(GEN9_GAMT_ECO_REG_RW_IA) |
		   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
}