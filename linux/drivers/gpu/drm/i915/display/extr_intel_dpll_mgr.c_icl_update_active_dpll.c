#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_encoder {scalar_t__ type; int /*<<< orphan*/  base; } ;
struct intel_digital_port {scalar_t__ tc_mode; } ;
struct intel_crtc_state {int dummy; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
typedef  enum icl_port_dpll_id { ____Placeholder_icl_port_dpll_id } icl_port_dpll_id ;
struct TYPE_2__ {struct intel_digital_port* primary; } ;

/* Variables and functions */
 int ICL_PORT_DPLL_DEFAULT ; 
 int ICL_PORT_DPLL_MG_PHY ; 
 scalar_t__ INTEL_OUTPUT_DP_MST ; 
 scalar_t__ TC_PORT_DP_ALT ; 
 scalar_t__ TC_PORT_LEGACY ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 TYPE_1__* enc_to_mst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_set_active_port_dpll (struct intel_crtc_state*,int) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 

__attribute__((used)) static void icl_update_active_dpll(struct intel_atomic_state *state,
				   struct intel_crtc *crtc,
				   struct intel_encoder *encoder)
{
	struct intel_crtc_state *crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	struct intel_digital_port *primary_port;
	enum icl_port_dpll_id port_dpll_id = ICL_PORT_DPLL_DEFAULT;

	primary_port = encoder->type == INTEL_OUTPUT_DP_MST ?
		enc_to_mst(&encoder->base)->primary :
		enc_to_dig_port(&encoder->base);

	if (primary_port &&
	    (primary_port->tc_mode == TC_PORT_DP_ALT ||
	     primary_port->tc_mode == TC_PORT_LEGACY))
		port_dpll_id = ICL_PORT_DPLL_MG_PHY;

	icl_set_active_port_dpll(crtc_state, port_dpll_id);
}