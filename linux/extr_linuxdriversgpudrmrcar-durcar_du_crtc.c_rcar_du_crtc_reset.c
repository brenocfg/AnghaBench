#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct drm_crtc* crtc; } ;
struct TYPE_3__ {scalar_t__ index; int /*<<< orphan*/  source; } ;
struct rcar_du_crtc_state {TYPE_2__ state; TYPE_1__ crc; } ;
struct drm_crtc {TYPE_2__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VSP1_DU_CRC_NONE ; 
 struct rcar_du_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_crtc_atomic_destroy_state (struct drm_crtc*,TYPE_2__*) ; 

__attribute__((used)) static void rcar_du_crtc_reset(struct drm_crtc *crtc)
{
	struct rcar_du_crtc_state *state;

	if (crtc->state) {
		rcar_du_crtc_atomic_destroy_state(crtc, crtc->state);
		crtc->state = NULL;
	}

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return;

	state->crc.source = VSP1_DU_CRC_NONE;
	state->crc.index = 0;

	crtc->state = &state->state;
	crtc->state->crtc = crtc;
}