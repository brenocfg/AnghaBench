#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xen_drm_front_drm_pipeline {int conn_connected; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_simple_display_pipe {TYPE_1__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ drm_dev_enter (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 int /*<<< orphan*/  send_pending_event (struct xen_drm_front_drm_pipeline*) ; 
 struct xen_drm_front_drm_pipeline* to_xen_drm_pipeline (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  xen_drm_front_fb_to_cookie (int /*<<< orphan*/ *) ; 
 int xen_drm_front_mode_set (struct xen_drm_front_drm_pipeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void display_disable(struct drm_simple_display_pipe *pipe)
{
	struct xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(pipe);
	int ret = 0, idx;

	if (drm_dev_enter(pipe->crtc.dev, &idx)) {
		ret = xen_drm_front_mode_set(pipeline, 0, 0, 0, 0, 0,
					     xen_drm_front_fb_to_cookie(NULL));
		drm_dev_exit(idx);
	}
	if (ret)
		DRM_ERROR("Failed to disable display: %d\n", ret);

	/* Make sure we can restart with enabled connector next time */
	pipeline->conn_connected = true;

	/* release stalled event if any */
	send_pending_event(pipeline);
}