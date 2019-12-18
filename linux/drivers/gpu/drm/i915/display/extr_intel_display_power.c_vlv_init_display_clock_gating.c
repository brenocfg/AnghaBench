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
struct drm_i915_private {scalar_t__ rawclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBR1_VLV ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (scalar_t__,int) ; 
 int /*<<< orphan*/  DPOUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  DSPCLK_GATE_D ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MI_ARB_VLV ; 
 int /*<<< orphan*/  RAWCLK_FREQ_VLV ; 
 int /*<<< orphan*/  VRHUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void vlv_init_display_clock_gating(struct drm_i915_private *dev_priv)
{
	u32 val;

	/*
	 * On driver load, a pipe may be active and driving a DSI display.
	 * Preserve DPOUNIT_CLOCK_GATE_DISABLE to avoid the pipe getting stuck
	 * (and never recovering) in this case. intel_dsi_post_disable() will
	 * clear it when we turn off the display.
	 */
	val = I915_READ(DSPCLK_GATE_D);
	val &= DPOUNIT_CLOCK_GATE_DISABLE;
	val |= VRHUNIT_CLOCK_GATE_DISABLE;
	I915_WRITE(DSPCLK_GATE_D, val);

	/*
	 * Disable trickle feed and enable pnd deadline calculation
	 */
	I915_WRITE(MI_ARB_VLV, MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE);
	I915_WRITE(CBR1_VLV, 0);

	WARN_ON(dev_priv->rawclk_freq == 0);

	I915_WRITE(RAWCLK_FREQ_VLV,
		   DIV_ROUND_CLOSEST(dev_priv->rawclk_freq, 1000));
}