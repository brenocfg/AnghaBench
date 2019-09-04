#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vmw_private {int dummy; } ;
struct vmw_framebuffer {scalar_t__ bo; } ;
struct vmw_fence_obj {int dummy; } ;
struct drm_vmw_rect {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {TYPE_3__ vbl; } ;
struct TYPE_12__ {struct drm_file* file_priv; } ;
struct drm_pending_vblank_event {TYPE_4__ event; TYPE_6__ base; } ;
struct drm_file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_crtc {TYPE_5__* state; TYPE_2__ mode; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {struct drm_pending_vblank_event* event; } ;
struct TYPE_7__ {scalar_t__ fb; struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_event_fence_action_queue (struct drm_file*,struct vmw_fence_obj*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_fence_obj_unreference (struct vmw_fence_obj**) ; 
 struct vmw_framebuffer* vmw_framebuffer_to_vfb (scalar_t__) ; 
 int vmw_kms_sou_do_bo_dirty (struct vmw_private*,struct vmw_framebuffer*,int /*<<< orphan*/ *,struct drm_vmw_rect*,int,int,int,struct vmw_fence_obj**,struct drm_crtc*) ; 
 int vmw_kms_sou_do_surface_dirty (struct vmw_private*,struct vmw_framebuffer*,int /*<<< orphan*/ *,struct drm_vmw_rect*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct vmw_fence_obj**,struct drm_crtc*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmw_sou_primary_plane_atomic_update(struct drm_plane *plane,
				    struct drm_plane_state *old_state)
{
	struct drm_crtc *crtc = plane->state->crtc;
	struct drm_pending_vblank_event *event = NULL;
	struct vmw_fence_obj *fence = NULL;
	int ret;

	if (crtc && plane->state->fb) {
		struct vmw_private *dev_priv = vmw_priv(crtc->dev);
		struct vmw_framebuffer *vfb =
			vmw_framebuffer_to_vfb(plane->state->fb);
		struct drm_vmw_rect vclips;

		vclips.x = crtc->x;
		vclips.y = crtc->y;
		vclips.w = crtc->mode.hdisplay;
		vclips.h = crtc->mode.vdisplay;

		if (vfb->bo)
			ret = vmw_kms_sou_do_bo_dirty(dev_priv, vfb, NULL,
						      &vclips, 1, 1, true,
						      &fence, crtc);
		else
			ret = vmw_kms_sou_do_surface_dirty(dev_priv, vfb, NULL,
							   &vclips, NULL, 0, 0,
							   1, 1, &fence, crtc);

		/*
		 * We cannot really fail this function, so if we do, then output
		 * an error and maintain consistent atomic state.
		 */
		if (ret != 0)
			DRM_ERROR("Failed to update screen.\n");
	} else {
		/*
		 * When disabling a plane, CRTC and FB should always be NULL
		 * together, otherwise it's an error.
		 * Here primary plane is being disable so should really blank
		 * the screen object display unit, if not already done.
		 */
		return;
	}

	event = crtc->state->event;
	/*
	 * In case of failure and other cases, vblank event will be sent in
	 * vmw_du_crtc_atomic_flush.
	 */
	if (event && fence) {
		struct drm_file *file_priv = event->base.file_priv;

		ret = vmw_event_fence_action_queue(file_priv,
						   fence,
						   &event->base,
						   &event->event.vbl.tv_sec,
						   &event->event.vbl.tv_usec,
						   true);

		if (unlikely(ret != 0))
			DRM_ERROR("Failed to queue event on fence.\n");
		else
			crtc->state->event = NULL;
	}

	if (fence)
		vmw_fence_obj_unreference(&fence);
}