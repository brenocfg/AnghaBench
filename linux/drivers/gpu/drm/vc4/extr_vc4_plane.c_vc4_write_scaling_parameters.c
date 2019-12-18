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
struct vc4_plane_state {scalar_t__* x_scaling; scalar_t__* y_scaling; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/ * src_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/ * src_w; } ;
struct drm_plane_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ VC4_SCALING_PPF ; 
 scalar_t__ VC4_SCALING_TPZ ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vc4_dlist_write (struct vc4_plane_state*,int) ; 
 int /*<<< orphan*/  vc4_write_ppf (struct vc4_plane_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_write_tpz (struct vc4_plane_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_write_scaling_parameters(struct drm_plane_state *state,
					 int channel)
{
	struct vc4_plane_state *vc4_state = to_vc4_plane_state(state);

	/* Ch0 H-PPF Word 0: Scaling Parameters */
	if (vc4_state->x_scaling[channel] == VC4_SCALING_PPF) {
		vc4_write_ppf(vc4_state,
			      vc4_state->src_w[channel], vc4_state->crtc_w);
	}

	/* Ch0 V-PPF Words 0-1: Scaling Parameters, Context */
	if (vc4_state->y_scaling[channel] == VC4_SCALING_PPF) {
		vc4_write_ppf(vc4_state,
			      vc4_state->src_h[channel], vc4_state->crtc_h);
		vc4_dlist_write(vc4_state, 0xc0c0c0c0);
	}

	/* Ch0 H-TPZ Words 0-1: Scaling Parameters, Recip */
	if (vc4_state->x_scaling[channel] == VC4_SCALING_TPZ) {
		vc4_write_tpz(vc4_state,
			      vc4_state->src_w[channel], vc4_state->crtc_w);
	}

	/* Ch0 V-TPZ Words 0-2: Scaling Parameters, Recip, Context */
	if (vc4_state->y_scaling[channel] == VC4_SCALING_TPZ) {
		vc4_write_tpz(vc4_state,
			      vc4_state->src_h[channel], vc4_state->crtc_h);
		vc4_dlist_write(vc4_state, 0xc0c0c0c0);
	}
}