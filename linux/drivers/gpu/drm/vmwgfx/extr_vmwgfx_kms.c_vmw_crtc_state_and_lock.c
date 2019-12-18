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
struct drm_crtc_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ mutex; } ;
struct drm_crtc {struct drm_crtc_state* state; TYPE_2__ mutex; } ;
struct drm_atomic_state {int /*<<< orphan*/  acquire_ctx; } ;

/* Variables and functions */
 int EALREADY ; 
 struct drm_crtc_state* ERR_PTR (int) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 int drm_modeset_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_crtc_state *
vmw_crtc_state_and_lock(struct drm_atomic_state *state, struct drm_crtc *crtc)
{
	struct drm_crtc_state *crtc_state;

	crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
	if (crtc_state) {
		lockdep_assert_held(&crtc->mutex.mutex.base);
	} else {
		int ret = drm_modeset_lock(&crtc->mutex, state->acquire_ctx);

		if (ret != 0 && ret != -EALREADY)
			return ERR_PTR(ret);

		crtc_state = crtc->state;
	}

	return crtc_state;
}