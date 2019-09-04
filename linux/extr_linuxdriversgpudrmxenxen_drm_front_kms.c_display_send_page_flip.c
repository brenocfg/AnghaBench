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
struct xen_drm_front_drm_pipeline {int conn_connected; int /*<<< orphan*/  index; int /*<<< orphan*/  pflip_to_worker; struct xen_drm_front_drm_info* drm_info; } ;
struct xen_drm_front_drm_info {int /*<<< orphan*/  front_info; } ;
struct drm_simple_display_pipe {int /*<<< orphan*/  plane; } ;
struct drm_plane_state {scalar_t__ fb; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  FRAME_DONE_TO_MS ; 
 struct drm_plane_state* drm_atomic_get_new_plane_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xen_drm_front_drm_pipeline* to_xen_drm_pipeline (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  xen_drm_front_fb_to_cookie (scalar_t__) ; 
 int xen_drm_front_page_flip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool display_send_page_flip(struct drm_simple_display_pipe *pipe,
				   struct drm_plane_state *old_plane_state)
{
	struct drm_plane_state *plane_state =
			drm_atomic_get_new_plane_state(old_plane_state->state,
						       &pipe->plane);

	/*
	 * If old_plane_state->fb is NULL and plane_state->fb is not,
	 * then this is an atomic commit which will enable display.
	 * If old_plane_state->fb is not NULL and plane_state->fb is,
	 * then this is an atomic commit which will disable display.
	 * Ignore these and do not send page flip as this framebuffer will be
	 * sent to the backend as a part of display_set_config call.
	 */
	if (old_plane_state->fb && plane_state->fb) {
		struct xen_drm_front_drm_pipeline *pipeline =
				to_xen_drm_pipeline(pipe);
		struct xen_drm_front_drm_info *drm_info = pipeline->drm_info;
		int ret;

		schedule_delayed_work(&pipeline->pflip_to_worker,
				      msecs_to_jiffies(FRAME_DONE_TO_MS));

		ret = xen_drm_front_page_flip(drm_info->front_info,
					      pipeline->index,
					      xen_drm_front_fb_to_cookie(plane_state->fb));
		if (ret) {
			DRM_ERROR("Failed to send page flip request to backend: %d\n", ret);

			pipeline->conn_connected = false;
			/*
			 * Report the flip not handled, so pending event is
			 * sent, unblocking user-space.
			 */
			return false;
		}
		/*
		 * Signal that page flip was handled, pending event will be sent
		 * on frame done event from the backend.
		 */
		return true;
	}

	return false;
}