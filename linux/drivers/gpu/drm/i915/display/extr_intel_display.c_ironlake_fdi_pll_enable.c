#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  fdi_lanes; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int FDI_DP_PORT_WIDTH (int /*<<< orphan*/ ) ; 
 int FDI_DP_PORT_WIDTH_MASK ; 
 int FDI_PCDCLK ; 
 int /*<<< orphan*/  FDI_RX_CTL (int) ; 
 int FDI_RX_PLL_ENABLE ; 
 int /*<<< orphan*/  FDI_TX_CTL (int) ; 
 int FDI_TX_PLL_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_BPC_MASK ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ironlake_fdi_pll_enable(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(intel_crtc->base.dev);
	int pipe = intel_crtc->pipe;
	i915_reg_t reg;
	u32 temp;

	/* enable PCH FDI RX PLL, wait warmup plus DMI latency */
	reg = FDI_RX_CTL(pipe);
	temp = I915_READ(reg);
	temp &= ~(FDI_DP_PORT_WIDTH_MASK | (0x7 << 16));
	temp |= FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
	temp |= (I915_READ(PIPECONF(pipe)) & PIPECONF_BPC_MASK) << 11;
	I915_WRITE(reg, temp | FDI_RX_PLL_ENABLE);

	POSTING_READ(reg);
	udelay(200);

	/* Switch from Rawclk to PCDclk */
	temp = I915_READ(reg);
	I915_WRITE(reg, temp | FDI_PCDCLK);

	POSTING_READ(reg);
	udelay(200);

	/* Enable CPU FDI TX PLL, always on for Ironlake */
	reg = FDI_TX_CTL(pipe);
	temp = I915_READ(reg);
	if ((temp & FDI_TX_PLL_ENABLE) == 0) {
		I915_WRITE(reg, temp | FDI_TX_PLL_ENABLE);

		POSTING_READ(reg);
		udelay(100);
	}
}