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
struct intel_crtc_state {int /*<<< orphan*/  dpll_hw_state; int /*<<< orphan*/  shared_dpll; struct icl_port_dpll* icl_port_dplls; } ;
struct icl_port_dpll {int /*<<< orphan*/  hw_state; int /*<<< orphan*/  pll; } ;
typedef  enum icl_port_dpll_id { ____Placeholder_icl_port_dpll_id } icl_port_dpll_id ;

/* Variables and functions */

void icl_set_active_port_dpll(struct intel_crtc_state *crtc_state,
			      enum icl_port_dpll_id port_dpll_id)
{
	struct icl_port_dpll *port_dpll =
		&crtc_state->icl_port_dplls[port_dpll_id];

	crtc_state->shared_dpll = port_dpll->pll;
	crtc_state->dpll_hw_state = port_dpll->hw_state;
}