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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int CL_UNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  CM0_PIPELINED_RENDER_FLUSH_DISABLE ; 
 int /*<<< orphan*/  DSPCLK_GATE_D ; 
 int DSSUNIT_CLOCK_GATE_DISABLE ; 
 int GS_UNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GM45 (struct drm_i915_private*) ; 
 int OVCUNIT_CLOCK_GATE_DISABLE ; 
 int OVRUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  RAMCLK_GATE_D ; 
 int /*<<< orphan*/  RC_OP_FLUSH_ENABLE ; 
 int /*<<< orphan*/  RENCLK_GATE_D1 ; 
 int /*<<< orphan*/  RENCLK_GATE_D2 ; 
 int VF_UNIT_CLOCK_GATE_DISABLE ; 
 int VRHUNIT_CLOCK_GATE_DISABLE ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g4x_disable_trickle_feed (struct drm_i915_private*) ; 

__attribute__((used)) static void g4x_init_clock_gating(struct drm_i915_private *dev_priv)
{
	u32 dspclk_gate;

	I915_WRITE(RENCLK_GATE_D1, 0);
	I915_WRITE(RENCLK_GATE_D2, VF_UNIT_CLOCK_GATE_DISABLE |
		   GS_UNIT_CLOCK_GATE_DISABLE |
		   CL_UNIT_CLOCK_GATE_DISABLE);
	I915_WRITE(RAMCLK_GATE_D, 0);
	dspclk_gate = VRHUNIT_CLOCK_GATE_DISABLE |
		OVRUNIT_CLOCK_GATE_DISABLE |
		OVCUNIT_CLOCK_GATE_DISABLE;
	if (IS_GM45(dev_priv))
		dspclk_gate |= DSSUNIT_CLOCK_GATE_DISABLE;
	I915_WRITE(DSPCLK_GATE_D, dspclk_gate);

	/* WaDisableRenderCachePipelinedFlush */
	I915_WRITE(CACHE_MODE_0,
		   _MASKED_BIT_ENABLE(CM0_PIPELINED_RENDER_FLUSH_DISABLE));

	/* WaDisable_RenderCache_OperationalFlush:g4x */
	I915_WRITE(CACHE_MODE_0, _MASKED_BIT_DISABLE(RC_OP_FLUSH_ENABLE));

	g4x_disable_trickle_feed(dev_priv);
}