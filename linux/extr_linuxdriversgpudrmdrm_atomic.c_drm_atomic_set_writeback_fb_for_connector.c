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
struct drm_writeback_job {int /*<<< orphan*/  fb; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_1__ base; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,struct drm_connector_state*,...) ; 
 int ENOMEM ; 
 struct drm_writeback_job* drm_atomic_get_writeback_job (struct drm_connector_state*) ; 
 int /*<<< orphan*/  drm_framebuffer_assign (int /*<<< orphan*/ *,struct drm_framebuffer*) ; 

int drm_atomic_set_writeback_fb_for_connector(
		struct drm_connector_state *conn_state,
		struct drm_framebuffer *fb)
{
	struct drm_writeback_job *job =
		drm_atomic_get_writeback_job(conn_state);
	if (!job)
		return -ENOMEM;

	drm_framebuffer_assign(&job->fb, fb);

	if (fb)
		DRM_DEBUG_ATOMIC("Set [FB:%d] for connector state %p\n",
				 fb->base.id, conn_state);
	else
		DRM_DEBUG_ATOMIC("Set [NOFB] for connector state %p\n",
				 conn_state);

	return 0;
}