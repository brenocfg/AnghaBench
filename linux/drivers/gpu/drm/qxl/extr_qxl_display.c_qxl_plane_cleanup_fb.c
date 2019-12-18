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
struct qxl_bo {TYPE_3__* shadow; } ;
struct drm_plane_state {TYPE_4__* fb; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_8__ {struct drm_gem_object** obj; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_2__ tbo; } ;
struct TYPE_5__ {TYPE_4__* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  qxl_bo_unpin (struct qxl_bo*) ; 

__attribute__((used)) static void qxl_plane_cleanup_fb(struct drm_plane *plane,
				 struct drm_plane_state *old_state)
{
	struct drm_gem_object *obj;
	struct qxl_bo *user_bo;

	if (!old_state->fb) {
		/*
		 * we never executed prepare_fb, so there's nothing to
		 * unpin.
		 */
		return;
	}

	obj = old_state->fb->obj[0];
	user_bo = gem_to_qxl_bo(obj);
	qxl_bo_unpin(user_bo);

	if (old_state->fb != plane->state->fb && user_bo->shadow) {
		drm_gem_object_put_unlocked(&user_bo->shadow->tbo.base);
		user_bo->shadow = NULL;
	}
}