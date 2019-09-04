#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_crtc_commit {int /*<<< orphan*/  flip_done; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {int /*<<< orphan*/  name; TYPE_3__ base; } ;
struct drm_atomic_state {TYPE_4__* fake_commit; TYPE_2__* crtcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  flip_done; } ;
struct TYPE_6__ {struct drm_crtc* ptr; struct drm_crtc_commit* commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

void drm_atomic_helper_wait_for_flip_done(struct drm_device *dev,
					  struct drm_atomic_state *old_state)
{
	struct drm_crtc *crtc;
	int i;

	for (i = 0; i < dev->mode_config.num_crtc; i++) {
		struct drm_crtc_commit *commit = old_state->crtcs[i].commit;
		int ret;

		crtc = old_state->crtcs[i].ptr;

		if (!crtc || !commit)
			continue;

		ret = wait_for_completion_timeout(&commit->flip_done, 10 * HZ);
		if (ret == 0)
			DRM_ERROR("[CRTC:%d:%s] flip_done timed out\n",
				  crtc->base.id, crtc->name);
	}

	if (old_state->fake_commit)
		complete_all(&old_state->fake_commit->flip_done);
}