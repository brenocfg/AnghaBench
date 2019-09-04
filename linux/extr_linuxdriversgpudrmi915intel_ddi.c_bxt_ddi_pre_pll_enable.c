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
typedef  int /*<<< orphan*/  uint8_t ;
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int /*<<< orphan*/  lane_lat_optim_mask; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_ddi_phy_set_lane_optim_mask (struct intel_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_ddi_pre_pll_enable(struct intel_encoder *encoder,
				   const struct intel_crtc_state *pipe_config,
				   const struct drm_connector_state *conn_state)
{
	uint8_t mask = pipe_config->lane_lat_optim_mask;

	bxt_ddi_phy_set_lane_optim_mask(encoder, mask);
}