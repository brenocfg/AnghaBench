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
struct intel_dp_mst_encoder {struct intel_digital_port* primary; } ;
struct intel_digital_port {int /*<<< orphan*/  base; } ;
struct intel_crtc_state {int dummy; } ;

/* Variables and functions */
 struct intel_dp_mst_encoder* enc_to_mst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ddi_get_config (int /*<<< orphan*/ *,struct intel_crtc_state*) ; 

__attribute__((used)) static void intel_dp_mst_enc_get_config(struct intel_encoder *encoder,
					struct intel_crtc_state *pipe_config)
{
	struct intel_dp_mst_encoder *intel_mst = enc_to_mst(&encoder->base);
	struct intel_digital_port *intel_dig_port = intel_mst->primary;

	intel_ddi_get_config(&intel_dig_port->base, pipe_config);
}