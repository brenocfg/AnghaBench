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
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_GMBUSUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  SOUTH_DSPCLK_GATE_D ; 

__attribute__((used)) static void pch_gmbus_clock_gating(struct drm_i915_private *dev_priv,
				   bool enable)
{
	u32 val;

	val = I915_READ(SOUTH_DSPCLK_GATE_D);
	if (!enable)
		val |= PCH_GMBUSUNIT_CLOCK_GATE_DISABLE;
	else
		val &= ~PCH_GMBUSUNIT_CLOCK_GATE_DISABLE;
	I915_WRITE(SOUTH_DSPCLK_GATE_D, val);
}