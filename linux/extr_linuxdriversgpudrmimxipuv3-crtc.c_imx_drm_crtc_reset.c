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
struct TYPE_2__ {struct drm_crtc* crtc; scalar_t__ mode_blob; } ;
struct imx_crtc_state {TYPE_1__ base; } ;
struct drm_crtc {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_property_blob_put (scalar_t__) ; 
 struct imx_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct imx_crtc_state*,int /*<<< orphan*/ ,int) ; 
 struct imx_crtc_state* to_imx_crtc_state (TYPE_1__*) ; 

__attribute__((used)) static void imx_drm_crtc_reset(struct drm_crtc *crtc)
{
	struct imx_crtc_state *state;

	if (crtc->state) {
		if (crtc->state->mode_blob)
			drm_property_blob_put(crtc->state->mode_blob);

		state = to_imx_crtc_state(crtc->state);
		memset(state, 0, sizeof(*state));
	} else {
		state = kzalloc(sizeof(*state), GFP_KERNEL);
		if (!state)
			return;
		crtc->state = &state->base;
	}

	state->base.crtc = crtc;
}