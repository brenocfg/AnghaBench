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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_GMBUS_GATING_DIS ; 
 int /*<<< orphan*/  GEN9_CLKGATE_DIS_4 ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_gmbus_clock_gating(struct drm_i915_private *dev_priv,
				   bool enable)
{
	u32 val;

	val = I915_READ(GEN9_CLKGATE_DIS_4);
	if (!enable)
		val |= BXT_GMBUS_GATING_DIS;
	else
		val &= ~BXT_GMBUS_GATING_DIS;
	I915_WRITE(GEN9_CLKGATE_DIS_4, val);
}