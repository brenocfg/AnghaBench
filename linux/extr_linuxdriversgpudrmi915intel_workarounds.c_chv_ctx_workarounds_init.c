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
 int /*<<< orphan*/  CHV_HZ_8X8_MODE_IN_1X ; 
 int /*<<< orphan*/  GEN8_ROW_CHICKEN ; 
 int /*<<< orphan*/  HIZ_CHICKEN ; 
 int /*<<< orphan*/  STALL_DOP_GATING_DISABLE ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gen8_ctx_workarounds_init (struct drm_i915_private*) ; 

__attribute__((used)) static int chv_ctx_workarounds_init(struct drm_i915_private *dev_priv)
{
	int ret;

	ret = gen8_ctx_workarounds_init(dev_priv);
	if (ret)
		return ret;

	/* WaDisableThreadStallDopClockGating:chv */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN, STALL_DOP_GATING_DISABLE);

	/* Improve HiZ throughput on CHV. */
	WA_SET_BIT_MASKED(HIZ_CHICKEN, CHV_HZ_8X8_MODE_IN_1X);

	return 0;
}