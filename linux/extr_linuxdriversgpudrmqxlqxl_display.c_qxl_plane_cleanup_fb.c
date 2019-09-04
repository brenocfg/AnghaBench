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
struct qxl_bo {TYPE_1__* shadow; int /*<<< orphan*/  is_primary; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_4__ {struct drm_gem_object* obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  gem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  qxl_bo_unpin (struct qxl_bo*) ; 
 TYPE_2__* to_qxl_framebuffer (int /*<<< orphan*/ ) ; 

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

	obj = to_qxl_framebuffer(old_state->fb)->obj;
	user_bo = gem_to_qxl_bo(obj);
	qxl_bo_unpin(user_bo);

	if (user_bo->shadow && !user_bo->is_primary) {
		drm_gem_object_put_unlocked(&user_bo->shadow->gem_base);
		user_bo->shadow = NULL;
	}
}