#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int FDI_PCDCLK ; 
 int /*<<< orphan*/  FDI_RX_CTL (int /*<<< orphan*/ ) ; 
 int FDI_RX_ENABLE ; 
 int /*<<< orphan*/  FDI_RX_MISC (int /*<<< orphan*/ ) ; 
 int FDI_RX_PLL_ENABLE ; 
 int FDI_RX_PWRDN_LANE0_MASK ; 
 int FDI_RX_PWRDN_LANE0_VAL (int) ; 
 int FDI_RX_PWRDN_LANE1_MASK ; 
 int FDI_RX_PWRDN_LANE1_VAL (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  intel_ddi_clk_disable (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_disable_ddi_buf (struct intel_encoder*,struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_ddi_fdi_post_disable(struct intel_encoder *encoder,
				const struct intel_crtc_state *old_crtc_state,
				const struct drm_connector_state *old_conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 val;

	/*
	 * Bspec lists this as both step 13 (before DDI_BUF_CTL disable)
	 * and step 18 (after clearing PORT_CLK_SEL). Based on a BUN,
	 * step 13 is the correct place for it. Step 18 is where it was
	 * originally before the BUN.
	 */
	val = I915_READ(FDI_RX_CTL(PIPE_A));
	val &= ~FDI_RX_ENABLE;
	I915_WRITE(FDI_RX_CTL(PIPE_A), val);

	intel_disable_ddi_buf(encoder, old_crtc_state);
	intel_ddi_clk_disable(encoder);

	val = I915_READ(FDI_RX_MISC(PIPE_A));
	val &= ~(FDI_RX_PWRDN_LANE1_MASK | FDI_RX_PWRDN_LANE0_MASK);
	val |= FDI_RX_PWRDN_LANE1_VAL(2) | FDI_RX_PWRDN_LANE0_VAL(2);
	I915_WRITE(FDI_RX_MISC(PIPE_A), val);

	val = I915_READ(FDI_RX_CTL(PIPE_A));
	val &= ~FDI_PCDCLK;
	I915_WRITE(FDI_RX_CTL(PIPE_A), val);

	val = I915_READ(FDI_RX_CTL(PIPE_A));
	val &= ~FDI_RX_PLL_ENABLE;
	I915_WRITE(FDI_RX_CTL(PIPE_A), val);
}