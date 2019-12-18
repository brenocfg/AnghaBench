#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_crtc_state {struct drm_atomic_state* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {int /*<<< orphan*/  name; TYPE_3__ base; int /*<<< orphan*/  state; TYPE_1__* funcs; int /*<<< orphan*/  mutex; } ;
struct drm_atomic_state {TYPE_2__* crtcs; int /*<<< orphan*/  acquire_ctx; } ;
struct TYPE_5__ {struct drm_crtc* ptr; struct drm_crtc_state* new_state; int /*<<< orphan*/  old_state; struct drm_crtc_state* state; } ;
struct TYPE_4__ {struct drm_crtc_state* (* atomic_duplicate_state ) (struct drm_crtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_crtc_state*,struct drm_atomic_state*) ; 
 int ENOMEM ; 
 struct drm_crtc_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 int drm_crtc_index (struct drm_crtc*) ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_crtc_state* stub1 (struct drm_crtc*) ; 

struct drm_crtc_state *
drm_atomic_get_crtc_state(struct drm_atomic_state *state,
			  struct drm_crtc *crtc)
{
	int ret, index = drm_crtc_index(crtc);
	struct drm_crtc_state *crtc_state;

	WARN_ON(!state->acquire_ctx);

	crtc_state = drm_atomic_get_existing_crtc_state(state, crtc);
	if (crtc_state)
		return crtc_state;

	ret = drm_modeset_lock(&crtc->mutex, state->acquire_ctx);
	if (ret)
		return ERR_PTR(ret);

	crtc_state = crtc->funcs->atomic_duplicate_state(crtc);
	if (!crtc_state)
		return ERR_PTR(-ENOMEM);

	state->crtcs[index].state = crtc_state;
	state->crtcs[index].old_state = crtc->state;
	state->crtcs[index].new_state = crtc_state;
	state->crtcs[index].ptr = crtc;
	crtc_state->state = state;

	DRM_DEBUG_ATOMIC("Added [CRTC:%d:%s] %p state to %p\n",
			 crtc->base.id, crtc->name, crtc_state, state);

	return crtc_state;
}