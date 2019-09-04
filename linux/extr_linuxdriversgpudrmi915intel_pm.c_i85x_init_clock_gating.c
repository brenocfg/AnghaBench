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
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEM_DISPLAY_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MEM_MODE ; 
 int /*<<< orphan*/  MI_AGPBUSY_830_MODE ; 
 int /*<<< orphan*/  MI_AGPBUSY_INT_EN ; 
 int /*<<< orphan*/  MI_STATE ; 
 int /*<<< orphan*/  RENCLK_GATE_D1 ; 
 int SV_CLOCK_GATE_DISABLE ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i85x_init_clock_gating(struct drm_i915_private *dev_priv)
{
	I915_WRITE(RENCLK_GATE_D1, SV_CLOCK_GATE_DISABLE);

	/* interrupts should cause a wake up from C3 */
	I915_WRITE(MI_STATE, _MASKED_BIT_ENABLE(MI_AGPBUSY_INT_EN) |
		   _MASKED_BIT_DISABLE(MI_AGPBUSY_830_MODE));

	I915_WRITE(MEM_MODE,
		   _MASKED_BIT_ENABLE(MEM_DISPLAY_TRICKLE_FEED_DISABLE));
}