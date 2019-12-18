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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dsi {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_SEQ_BACKLIGHT_ON ; 
 struct intel_dsi* enc_to_intel_dsi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen11_dsi_enable_port_and_phy (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  gen11_dsi_enable_transcoder (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_map_pll (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  gen11_dsi_powerup_panel (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_set_transcoder_timings (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_dsi_vbt_exec_sequence (struct intel_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_panel_enable_backlight (struct intel_crtc_state const*,struct drm_connector_state const*) ; 

__attribute__((used)) static void gen11_dsi_pre_enable(struct intel_encoder *encoder,
				 const struct intel_crtc_state *pipe_config,
				 const struct drm_connector_state *conn_state)
{
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);

	/* step3b */
	gen11_dsi_map_pll(encoder, pipe_config);

	/* step4: enable DSI port and DPHY */
	gen11_dsi_enable_port_and_phy(encoder, pipe_config);

	/* step5: program and powerup panel */
	gen11_dsi_powerup_panel(encoder);

	/* step6c: configure transcoder timings */
	gen11_dsi_set_transcoder_timings(encoder, pipe_config);

	/* step6d: enable dsi transcoder */
	gen11_dsi_enable_transcoder(encoder);

	/* step7: enable backlight */
	intel_panel_enable_backlight(pipe_config, conn_state);
	intel_dsi_vbt_exec_sequence(intel_dsi, MIPI_SEQ_BACKLIGHT_ON);
}