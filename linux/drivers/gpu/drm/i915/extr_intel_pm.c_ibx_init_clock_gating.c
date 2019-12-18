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
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_DPLSUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  SOUTH_DSPCLK_GATE_D ; 

__attribute__((used)) static void ibx_init_clock_gating(struct drm_i915_private *dev_priv)
{
	/*
	 * On Ibex Peak and Cougar Point, we need to disable clock
	 * gating for the panel power sequencer or it will fail to
	 * start up when no ports are active.
	 */
	I915_WRITE(SOUTH_DSPCLK_GATE_D, PCH_DPLSUNIT_CLOCK_GATE_DISABLE);
}