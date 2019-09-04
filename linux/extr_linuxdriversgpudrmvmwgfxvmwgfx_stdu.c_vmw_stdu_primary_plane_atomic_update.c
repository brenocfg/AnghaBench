#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vmw_screen_target_display_unit {int /*<<< orphan*/  defined; TYPE_2__* display_srf; int /*<<< orphan*/  cpp; int /*<<< orphan*/  content_fb_type; } ;
struct vmw_private {int dummy; } ;
struct vmw_plane_state {int /*<<< orphan*/  cpp; int /*<<< orphan*/  content_fb_type; TYPE_2__* surf; } ;
struct vmw_framebuffer {scalar_t__ bo; } ;
struct vmw_fence_obj {int dummy; } ;
struct drm_vmw_rect {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct drm_plane_state {struct drm_crtc* crtc; } ;
struct drm_plane {TYPE_6__* state; } ;
struct TYPE_10__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {TYPE_3__ vbl; } ;
struct TYPE_14__ {struct drm_file* file_priv; } ;
struct drm_pending_vblank_event {TYPE_4__ event; TYPE_7__ base; } ;
struct drm_file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_crtc {TYPE_5__* state; int /*<<< orphan*/  dev; TYPE_1__ mode; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {scalar_t__ fb; struct drm_crtc* crtc; } ;
struct TYPE_12__ {struct drm_pending_vblank_event* event; } ;
struct TYPE_9__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct vmw_screen_target_display_unit* vmw_crtc_to_stdu (struct drm_crtc*) ; 
 int vmw_event_fence_action_queue (struct drm_file*,struct vmw_fence_obj*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_execbuf_fence_commands (int /*<<< orphan*/ *,struct vmw_private*,struct vmw_fence_obj**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_fence_obj_unreference (struct vmw_fence_obj**) ; 
 int /*<<< orphan*/  vmw_fifo_flush (struct vmw_private*,int) ; 
 struct vmw_framebuffer* vmw_framebuffer_to_vfb (scalar_t__) ; 
 int vmw_kms_stdu_dma (struct vmw_private*,int /*<<< orphan*/ *,struct vmw_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_vmw_rect*,int,int,int,int,struct drm_crtc*) ; 
 int vmw_kms_stdu_surface_dirty (struct vmw_private*,struct vmw_framebuffer*,int /*<<< orphan*/ *,struct drm_vmw_rect*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,struct drm_crtc*) ; 
 struct vmw_plane_state* vmw_plane_state_to_vps (TYPE_6__*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 
 int vmw_stdu_bind_st (struct vmw_private*,struct vmw_screen_target_display_unit*,int /*<<< orphan*/ *) ; 
 int vmw_stdu_update_st (struct vmw_private*,struct vmw_screen_target_display_unit*) ; 

__attribute__((used)) static void
vmw_stdu_primary_plane_atomic_update(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct vmw_plane_state *vps = vmw_plane_state_to_vps(plane->state);
	struct drm_crtc *crtc = plane->state->crtc;
	struct vmw_screen_target_display_unit *stdu;
	struct drm_pending_vblank_event *event;
	struct vmw_private *dev_priv;
	int ret;

	/*
	 * We cannot really fail this function, so if we do, then output an
	 * error and maintain consistent atomic state.
	 */
	if (crtc && plane->state->fb) {
		struct vmw_framebuffer *vfb =
			vmw_framebuffer_to_vfb(plane->state->fb);
		struct drm_vmw_rect vclips;
		stdu = vmw_crtc_to_stdu(crtc);
		dev_priv = vmw_priv(crtc->dev);

		stdu->display_srf = vps->surf;
		stdu->content_fb_type = vps->content_fb_type;
		stdu->cpp = vps->cpp;

		vclips.x = crtc->x;
		vclips.y = crtc->y;
		vclips.w = crtc->mode.hdisplay;
		vclips.h = crtc->mode.vdisplay;

		ret = vmw_stdu_bind_st(dev_priv, stdu, &stdu->display_srf->res);
		if (ret)
			DRM_ERROR("Failed to bind surface to STDU.\n");

		if (vfb->bo)
			ret = vmw_kms_stdu_dma(dev_priv, NULL, vfb, NULL, NULL,
					       &vclips, 1, 1, true, false,
					       crtc);
		else
			ret = vmw_kms_stdu_surface_dirty(dev_priv, vfb, NULL,
							 &vclips, NULL, 0, 0,
							 1, 1, NULL, crtc);
		if (ret)
			DRM_ERROR("Failed to update STDU.\n");
	} else {
		crtc = old_state->crtc;
		stdu = vmw_crtc_to_stdu(crtc);
		dev_priv = vmw_priv(crtc->dev);

		/*
		 * When disabling a plane, CRTC and FB should always be NULL
		 * together, otherwise it's an error.
		 * Here primary plane is being disable so blank the screen
		 * target display unit, if not already done.
		 */
		if (!stdu->defined)
			return;

		ret = vmw_stdu_bind_st(dev_priv, stdu, NULL);
		if (ret)
			DRM_ERROR("Failed to blank STDU\n");

		ret = vmw_stdu_update_st(dev_priv, stdu);
		if (ret)
			DRM_ERROR("Failed to update STDU.\n");

		return;
	}

	event = crtc->state->event;
	/*
	 * In case of failure and other cases, vblank event will be sent in
	 * vmw_du_crtc_atomic_flush.
	 */
	if (event && (ret == 0)) {
		struct vmw_fence_obj *fence = NULL;
		struct drm_file *file_priv = event->base.file_priv;

		vmw_execbuf_fence_commands(NULL, dev_priv, &fence, NULL);

		/*
		 * If fence is NULL, then already sync.
		 */
		if (fence) {
			ret = vmw_event_fence_action_queue(
				file_priv, fence, &event->base,
				&event->event.vbl.tv_sec,
				&event->event.vbl.tv_usec,
				true);
			if (ret)
				DRM_ERROR("Failed to queue event on fence.\n");
			else
				crtc->state->event = NULL;

			vmw_fence_obj_unreference(&fence);
		}
	} else {
		(void) vmw_fifo_flush(dev_priv, false);
	}
}