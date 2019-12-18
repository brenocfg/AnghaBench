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
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen11_dsi_enable_io_power (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_program_esc_clk_div (struct intel_encoder*) ; 

__attribute__((used)) static void gen11_dsi_pre_pll_enable(struct intel_encoder *encoder,
				     const struct intel_crtc_state *pipe_config,
				     const struct drm_connector_state *conn_state)
{
	/* step2: enable IO power */
	gen11_dsi_enable_io_power(encoder);

	/* step3: enable DSI PLL */
	gen11_dsi_program_esc_clk_div(encoder);
}