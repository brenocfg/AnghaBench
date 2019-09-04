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
struct intel_dp {int DP; int /*<<< orphan*/  lane_count; } ;
struct intel_digital_port {int saved_port_bits; } ;

/* Variables and functions */
 int DDI_BUF_CTL_ENABLE ; 
 int DDI_BUF_TRANS_SELECT (int /*<<< orphan*/ ) ; 
 int DDI_PORT_WIDTH (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_ddi_init_dp_buf_reg(struct intel_encoder *encoder)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_digital_port *intel_dig_port =
		enc_to_dig_port(&encoder->base);

	intel_dp->DP = intel_dig_port->saved_port_bits |
		DDI_BUF_CTL_ENABLE | DDI_BUF_TRANS_SELECT(0);
	intel_dp->DP |= DDI_PORT_WIDTH(intel_dp->lane_count);
}