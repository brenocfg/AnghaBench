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
struct drm_crtc_state {struct drm_crtc_commit* commit; } ;
struct drm_crtc_commit {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {struct drm_crtc_commit* fake_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 int /*<<< orphan*/  init_commit (struct drm_crtc_commit*,int /*<<< orphan*/ *) ; 
 struct drm_crtc_commit* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_commit *
crtc_or_fake_commit(struct drm_atomic_state *state, struct drm_crtc *crtc)
{
	if (crtc) {
		struct drm_crtc_state *new_crtc_state;

		new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);

		return new_crtc_state->commit;
	}

	if (!state->fake_commit) {
		state->fake_commit = kzalloc(sizeof(*state->fake_commit), GFP_KERNEL);
		if (!state->fake_commit)
			return NULL;

		init_commit(state->fake_commit, NULL);
	}

	return state->fake_commit;
}