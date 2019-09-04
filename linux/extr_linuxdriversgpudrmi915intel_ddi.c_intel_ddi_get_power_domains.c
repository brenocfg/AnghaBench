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
typedef  int /*<<< orphan*/  u64 ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {struct intel_dp dp; int /*<<< orphan*/  ddi_io_power_domain; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_main_link_aux_domain (struct intel_dp*) ; 

__attribute__((used)) static u64 intel_ddi_get_power_domains(struct intel_encoder *encoder,
				       struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *dig_port;
	u64 domains;

	/*
	 * TODO: Add support for MST encoders. Atm, the following should never
	 * happen since fake-MST encoders don't set their get_power_domains()
	 * hook.
	 */
	if (WARN_ON(intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST)))
		return 0;

	dig_port = enc_to_dig_port(&encoder->base);
	domains = BIT_ULL(dig_port->ddi_io_power_domain);

	/* AUX power is only needed for (e)DP mode, not for HDMI. */
	if (intel_crtc_has_dp_encoder(crtc_state)) {
		struct intel_dp *intel_dp = &dig_port->dp;

		domains |= BIT_ULL(intel_ddi_main_link_aux_domain(intel_dp));
	}

	return domains;
}