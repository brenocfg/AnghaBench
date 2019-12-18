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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {scalar_t__ active; } ;
struct intel_crtc_state {int lane_count; TYPE_1__ base; } ;
struct intel_crtc {scalar_t__ active; } ;
struct intel_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  enc_to_dig_port (int /*<<< orphan*/ *) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_tc_port_get_link (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_update_active_dpll (struct intel_atomic_state*,struct intel_crtc*,struct intel_encoder*) ; 

__attribute__((used)) static void
intel_ddi_update_prepare(struct intel_atomic_state *state,
			 struct intel_encoder *encoder,
			 struct intel_crtc *crtc)
{
	struct intel_crtc_state *crtc_state =
		crtc ? intel_atomic_get_new_crtc_state(state, crtc) : NULL;
	int required_lanes = crtc_state ? crtc_state->lane_count : 1;

	WARN_ON(crtc && crtc->active);

	intel_tc_port_get_link(enc_to_dig_port(&encoder->base), required_lanes);
	if (crtc_state && crtc_state->base.active)
		intel_update_active_dpll(state, crtc, encoder);
}