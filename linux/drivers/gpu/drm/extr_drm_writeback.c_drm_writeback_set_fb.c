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
struct drm_framebuffer {int dummy; } ;
struct drm_connector_state {TYPE_1__* writeback_job; TYPE_2__* connector; } ;
struct TYPE_4__ {scalar_t__ connector_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  fb; int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_WRITEBACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_connector_to_writeback (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_framebuffer_assign (int /*<<< orphan*/ *,struct drm_framebuffer*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

int drm_writeback_set_fb(struct drm_connector_state *conn_state,
			 struct drm_framebuffer *fb)
{
	WARN_ON(conn_state->connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK);

	if (!conn_state->writeback_job) {
		conn_state->writeback_job =
			kzalloc(sizeof(*conn_state->writeback_job), GFP_KERNEL);
		if (!conn_state->writeback_job)
			return -ENOMEM;

		conn_state->writeback_job->connector =
			drm_connector_to_writeback(conn_state->connector);
	}

	drm_framebuffer_assign(&conn_state->writeback_job->fb, fb);
	return 0;
}