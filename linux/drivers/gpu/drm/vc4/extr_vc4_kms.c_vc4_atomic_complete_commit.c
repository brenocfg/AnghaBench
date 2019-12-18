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
struct vc4_dev {int /*<<< orphan*/  async_modeset; } ;
struct vc4_crtc {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_atomic_state {TYPE_2__* crtcs; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_cleanup_done (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_hw_done (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_disables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_enables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_planes (struct drm_device*,struct drm_atomic_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_fake_vblank (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_wait_for_dependencies (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_wait_for_fences (struct drm_device*,struct drm_atomic_state*,int) ; 
 int /*<<< orphan*/  drm_atomic_helper_wait_for_flip_done (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 struct vc4_crtc* to_vc4_crtc (int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_ctm_commit (struct vc4_dev*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  vc4_hvs_mask_underrun (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vc4_atomic_complete_commit(struct drm_atomic_state *state)
{
	struct drm_device *dev = state->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_crtc *vc4_crtc;
	int i;

	for (i = 0; i < dev->mode_config.num_crtc; i++) {
		if (!state->crtcs[i].ptr || !state->crtcs[i].commit)
			continue;

		vc4_crtc = to_vc4_crtc(state->crtcs[i].ptr);
		vc4_hvs_mask_underrun(dev, vc4_crtc->channel);
	}

	drm_atomic_helper_wait_for_fences(dev, state, false);

	drm_atomic_helper_wait_for_dependencies(state);

	drm_atomic_helper_commit_modeset_disables(dev, state);

	vc4_ctm_commit(vc4, state);

	drm_atomic_helper_commit_planes(dev, state, 0);

	drm_atomic_helper_commit_modeset_enables(dev, state);

	drm_atomic_helper_fake_vblank(state);

	drm_atomic_helper_commit_hw_done(state);

	drm_atomic_helper_wait_for_flip_done(dev, state);

	drm_atomic_helper_cleanup_planes(dev, state);

	drm_atomic_helper_commit_cleanup_done(state);

	drm_atomic_state_put(state);

	up(&vc4->async_modeset);
}