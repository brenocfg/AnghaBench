#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_3__ base; } ;
struct intel_dsi {int pclk; scalar_t__ dual_link; } ;
struct TYPE_4__ {int crtc_clock; } ;
struct TYPE_5__ {TYPE_1__ adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  pipe_bpp; int /*<<< orphan*/  output_types; TYPE_2__ base; int /*<<< orphan*/  dpll_hw_state; int /*<<< orphan*/  port_clock; } ;
struct intel_crtc {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 int /*<<< orphan*/  bdw_get_pipemisc_bpp (struct intel_crtc*) ; 
 int /*<<< orphan*/  cnl_calc_wrpll_link (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 struct intel_dsi* enc_to_intel_dsi (TYPE_3__*) ; 
 int /*<<< orphan*/  gen11_dsi_get_timings (struct intel_encoder*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen11_dsi_get_config(struct intel_encoder *encoder,
				 struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_crtc *crtc = to_intel_crtc(pipe_config->base.crtc);
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);

	/* FIXME: adapt icl_ddi_clock_get() for DSI and use that? */
	pipe_config->port_clock =
		cnl_calc_wrpll_link(dev_priv, &pipe_config->dpll_hw_state);

	pipe_config->base.adjusted_mode.crtc_clock = intel_dsi->pclk;
	if (intel_dsi->dual_link)
		pipe_config->base.adjusted_mode.crtc_clock *= 2;

	gen11_dsi_get_timings(encoder, pipe_config);
	pipe_config->output_types |= BIT(INTEL_OUTPUT_DSI);
	pipe_config->pipe_bpp = bdw_get_pipemisc_bpp(crtc);
}