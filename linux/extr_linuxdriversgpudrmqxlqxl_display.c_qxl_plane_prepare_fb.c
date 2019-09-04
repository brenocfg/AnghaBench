#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qxl_device {int dummy; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct qxl_bo {TYPE_5__* shadow; TYPE_3__ gem_base; scalar_t__ is_dumb; } ;
struct drm_plane_state {scalar_t__ crtc; scalar_t__ crtc_w; scalar_t__ crtc_h; scalar_t__ src_x; scalar_t__ src_y; scalar_t__ src_w; scalar_t__ src_h; scalar_t__ rotation; scalar_t__ zpos; scalar_t__ fb; } ;
struct drm_plane {scalar_t__ type; TYPE_2__* state; TYPE_1__* dev; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  gem_base; } ;
struct TYPE_9__ {struct drm_gem_object* obj; } ;
struct TYPE_7__ {scalar_t__ crtc; scalar_t__ crtc_w; scalar_t__ crtc_h; scalar_t__ src_x; scalar_t__ src_y; scalar_t__ src_w; scalar_t__ src_h; scalar_t__ rotation; scalar_t__ zpos; scalar_t__ fb; } ;
struct TYPE_6__ {struct qxl_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  QXL_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  QXL_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  qxl_bo_create (struct qxl_device*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__**) ; 
 int qxl_bo_pin (struct qxl_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* to_qxl_framebuffer (scalar_t__) ; 

__attribute__((used)) static int qxl_plane_prepare_fb(struct drm_plane *plane,
				struct drm_plane_state *new_state)
{
	struct qxl_device *qdev = plane->dev->dev_private;
	struct drm_gem_object *obj;
	struct qxl_bo *user_bo, *old_bo = NULL;
	int ret;

	if (!new_state->fb)
		return 0;

	obj = to_qxl_framebuffer(new_state->fb)->obj;
	user_bo = gem_to_qxl_bo(obj);

	if (plane->type == DRM_PLANE_TYPE_PRIMARY &&
	    user_bo->is_dumb && !user_bo->shadow) {
		if (plane->state->fb) {
			obj = to_qxl_framebuffer(plane->state->fb)->obj;
			old_bo = gem_to_qxl_bo(obj);
		}
		if (old_bo && old_bo->shadow &&
		    user_bo->gem_base.size == old_bo->gem_base.size &&
		    plane->state->crtc     == new_state->crtc &&
		    plane->state->crtc_w   == new_state->crtc_w &&
		    plane->state->crtc_h   == new_state->crtc_h &&
		    plane->state->src_x    == new_state->src_x &&
		    plane->state->src_y    == new_state->src_y &&
		    plane->state->src_w    == new_state->src_w &&
		    plane->state->src_h    == new_state->src_h &&
		    plane->state->rotation == new_state->rotation &&
		    plane->state->zpos     == new_state->zpos) {
			drm_gem_object_get(&old_bo->shadow->gem_base);
			user_bo->shadow = old_bo->shadow;
		} else {
			qxl_bo_create(qdev, user_bo->gem_base.size,
				      true, true, QXL_GEM_DOMAIN_VRAM, NULL,
				      &user_bo->shadow);
		}
	}

	ret = qxl_bo_pin(user_bo, QXL_GEM_DOMAIN_CPU, NULL);
	if (ret)
		return ret;

	return 0;
}