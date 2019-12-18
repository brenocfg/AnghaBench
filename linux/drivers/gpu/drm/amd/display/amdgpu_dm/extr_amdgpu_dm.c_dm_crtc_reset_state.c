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
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {struct drm_crtc* crtc; } ;
struct dm_crtc_state {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dm_crtc_destroy_state (struct drm_crtc*,TYPE_1__*) ; 
 struct dm_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_crtc_reset_state(struct drm_crtc *crtc)
{
	struct dm_crtc_state *state;

	if (crtc->state)
		dm_crtc_destroy_state(crtc, crtc->state);

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (WARN_ON(!state))
		return;

	crtc->state = &state->base;
	crtc->state->crtc = crtc;

}