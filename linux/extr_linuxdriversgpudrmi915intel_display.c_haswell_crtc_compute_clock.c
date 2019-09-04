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
struct intel_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct intel_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DSI ; 
 int /*<<< orphan*/  intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct intel_encoder* intel_get_crtc_new_encoder (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_get_shared_dpll (struct intel_crtc*,struct intel_crtc_state*,struct intel_encoder*) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int haswell_crtc_compute_clock(struct intel_crtc *crtc,
				      struct intel_crtc_state *crtc_state)
{
	struct intel_atomic_state *state =
		to_intel_atomic_state(crtc_state->base.state);

	if (!intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI)) {
		struct intel_encoder *encoder =
			intel_get_crtc_new_encoder(state, crtc_state);

		if (!intel_get_shared_dpll(crtc, crtc_state, encoder)) {
			DRM_DEBUG_DRIVER("failed to find PLL for pipe %c\n",
					 pipe_name(crtc->pipe));
			return -EINVAL;
		}
	}

	return 0;
}