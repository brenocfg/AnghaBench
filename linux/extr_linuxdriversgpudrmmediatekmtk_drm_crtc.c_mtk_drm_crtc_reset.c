#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct drm_crtc* crtc; } ;
struct mtk_crtc_state {TYPE_1__ base; } ;
struct drm_crtc {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (TYPE_1__*) ; 
 struct mtk_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mtk_crtc_state*,int /*<<< orphan*/ ,int) ; 
 struct mtk_crtc_state* to_mtk_crtc_state (TYPE_1__*) ; 

__attribute__((used)) static void mtk_drm_crtc_reset(struct drm_crtc *crtc)
{
	struct mtk_crtc_state *state;

	if (crtc->state) {
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

		state = to_mtk_crtc_state(crtc->state);
		memset(state, 0, sizeof(*state));
	} else {
		state = kzalloc(sizeof(*state), GFP_KERNEL);
		if (!state)
			return;
		crtc->state = &state->base;
	}

	state->base.crtc = crtc;
}