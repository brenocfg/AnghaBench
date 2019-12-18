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
struct intel_crtc_state {int /*<<< orphan*/ * shared_dpll; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;

/* Variables and functions */
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 struct intel_crtc_state* intel_atomic_get_old_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_unreference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_put_dpll(struct intel_atomic_state *state,
			   struct intel_crtc *crtc)
{
	const struct intel_crtc_state *old_crtc_state =
		intel_atomic_get_old_crtc_state(state, crtc);
	struct intel_crtc_state *new_crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);

	new_crtc_state->shared_dpll = NULL;

	if (!old_crtc_state->shared_dpll)
		return;

	intel_unreference_shared_dpll(state, crtc, old_crtc_state->shared_dpll);
}