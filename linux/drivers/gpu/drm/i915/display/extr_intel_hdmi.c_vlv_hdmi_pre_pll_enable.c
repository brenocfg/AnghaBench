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
 int /*<<< orphan*/  intel_hdmi_prepare (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  vlv_phy_pre_pll_enable (struct intel_encoder*,struct intel_crtc_state const*) ; 

__attribute__((used)) static void vlv_hdmi_pre_pll_enable(struct intel_encoder *encoder,
				    const struct intel_crtc_state *pipe_config,
				    const struct drm_connector_state *conn_state)
{
	intel_hdmi_prepare(encoder, pipe_config);

	vlv_phy_pre_pll_enable(encoder, pipe_config);
}