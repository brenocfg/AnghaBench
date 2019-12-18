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
struct drm_crtc_state {int dummy; } ;
struct omap_crtc_state {struct drm_crtc_state base; int /*<<< orphan*/  manually_updated; int /*<<< orphan*/  rotation; int /*<<< orphan*/  zpos; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct omap_crtc_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct omap_crtc_state* to_omap_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_state *
omap_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct omap_crtc_state *state, *current_state;

	if (WARN_ON(!crtc->state))
		return NULL;

	current_state = to_omap_crtc_state(crtc->state);

	state = kmalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	state->zpos = current_state->zpos;
	state->rotation = current_state->rotation;
	state->manually_updated = current_state->manually_updated;

	return &state->base;
}