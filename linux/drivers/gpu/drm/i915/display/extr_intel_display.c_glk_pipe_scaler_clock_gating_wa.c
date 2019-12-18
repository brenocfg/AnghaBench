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
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CLKGATE_DIS_PSL (int) ; 
 int DPFR_GATING_DIS ; 
 int DPF_GATING_DIS ; 
 int DPF_RAM_GATING_DIS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void glk_pipe_scaler_clock_gating_wa(struct drm_i915_private *dev_priv,
					    enum pipe pipe, bool apply)
{
	u32 val = I915_READ(CLKGATE_DIS_PSL(pipe));
	u32 mask = DPF_GATING_DIS | DPF_RAM_GATING_DIS | DPFR_GATING_DIS;

	if (apply)
		val |= mask;
	else
		val &= ~mask;

	I915_WRITE(CLKGATE_DIS_PSL(pipe), val);
}