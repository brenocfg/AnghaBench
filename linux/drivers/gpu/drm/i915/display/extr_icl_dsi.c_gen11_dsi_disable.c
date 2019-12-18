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
 int /*<<< orphan*/  MIPI_SEQ_BACKLIGHT_OFF ; 
 struct intel_dsi* enc_to_intel_dsi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen11_dsi_deconfigure_trancoder (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_disable_io_power (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_disable_port (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_disable_transcoder (struct intel_encoder*) ; 
 int /*<<< orphan*/  gen11_dsi_powerdown_panel (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_dsi_vbt_exec_sequence (struct intel_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_panel_disable_backlight (struct drm_connector_state const*) ; 

__attribute__((used)) static void gen11_dsi_disable(struct intel_encoder *encoder,
			      const struct intel_crtc_state *old_crtc_state,
			      const struct drm_connector_state *old_conn_state)
{
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(&encoder->base);

	/* step1: turn off backlight */
	intel_dsi_vbt_exec_sequence(intel_dsi, MIPI_SEQ_BACKLIGHT_OFF);
	intel_panel_disable_backlight(old_conn_state);

	/* step2d,e: disable transcoder and wait */
	gen11_dsi_disable_transcoder(encoder);

	/* step2f,g: powerdown panel */
	gen11_dsi_powerdown_panel(encoder);

	/* step2h,i,j: deconfig trancoder */
	gen11_dsi_deconfigure_trancoder(encoder);

	/* step3: disable port */
	gen11_dsi_disable_port(encoder);

	/* step4: disable IO power */
	gen11_dsi_disable_io_power(encoder);
}