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
struct intel_crtc_state {struct icl_port_dpll* icl_port_dplls; int /*<<< orphan*/ * shared_dpll; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct icl_port_dpll {int /*<<< orphan*/ * pll; } ;
typedef  enum icl_port_dpll_id { ____Placeholder_icl_port_dpll_id } icl_port_dpll_id ;

/* Variables and functions */
 int ICL_PORT_DPLL_COUNT ; 
 int ICL_PORT_DPLL_DEFAULT ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 struct intel_crtc_state* intel_atomic_get_old_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_unreference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icl_put_dplls(struct intel_atomic_state *state,
			  struct intel_crtc *crtc)
{
	const struct intel_crtc_state *old_crtc_state =
		intel_atomic_get_old_crtc_state(state, crtc);
	struct intel_crtc_state *new_crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	enum icl_port_dpll_id id;

	new_crtc_state->shared_dpll = NULL;

	for (id = ICL_PORT_DPLL_DEFAULT; id < ICL_PORT_DPLL_COUNT; id++) {
		const struct icl_port_dpll *old_port_dpll =
			&old_crtc_state->icl_port_dplls[id];
		struct icl_port_dpll *new_port_dpll =
			&new_crtc_state->icl_port_dplls[id];

		new_port_dpll->pll = NULL;

		if (!old_port_dpll->pll)
			continue;

		intel_unreference_shared_dpll(state, crtc, old_port_dpll->pll);
	}
}