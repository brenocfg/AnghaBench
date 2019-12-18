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
struct intel_encoder {int port; int /*<<< orphan*/  base; } ;
struct intel_dp {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int PORT_A ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_prepare (struct intel_encoder*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  ironlake_edp_pll_on (struct intel_dp*,struct intel_crtc_state const*) ; 

__attribute__((used)) static void g4x_pre_enable_dp(struct intel_encoder *encoder,
			      const struct intel_crtc_state *pipe_config,
			      const struct drm_connector_state *conn_state)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	enum port port = encoder->port;

	intel_dp_prepare(encoder, pipe_config);

	/* Only ilk+ has port A */
	if (port == PORT_A)
		ironlake_edp_pll_on(intel_dp, pipe_config);
}