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
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int /*<<< orphan*/  DEUC ; 
 int /*<<< orphan*/  DSPCLK_GATE_D ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I965_RCC_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MI_ARB_STATE ; 
 int /*<<< orphan*/  RAMCLK_GATE_D ; 
 int /*<<< orphan*/  RC_OP_FLUSH_ENABLE ; 
 int /*<<< orphan*/  RENCLK_GATE_D1 ; 
 int /*<<< orphan*/  RENCLK_GATE_D2 ; 
 int /*<<< orphan*/  _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i965gm_init_clock_gating(struct drm_i915_private *dev_priv)
{
	I915_WRITE(RENCLK_GATE_D1, I965_RCC_CLOCK_GATE_DISABLE);
	I915_WRITE(RENCLK_GATE_D2, 0);
	I915_WRITE(DSPCLK_GATE_D, 0);
	I915_WRITE(RAMCLK_GATE_D, 0);
	I915_WRITE16(DEUC, 0);
	I915_WRITE(MI_ARB_STATE,
		   _MASKED_BIT_ENABLE(MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE));

	/* WaDisable_RenderCache_OperationalFlush:gen4 */
	I915_WRITE(CACHE_MODE_0, _MASKED_BIT_DISABLE(RC_OP_FLUSH_ENABLE));
}