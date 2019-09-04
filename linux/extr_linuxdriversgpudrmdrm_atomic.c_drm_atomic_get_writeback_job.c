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
struct drm_writeback_job {int dummy; } ;
struct drm_connector_state {struct drm_writeback_job* writeback_job; TYPE_1__* connector; } ;
struct TYPE_2__ {scalar_t__ connector_type; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_WRITEBACK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_writeback_job* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_writeback_job *
drm_atomic_get_writeback_job(struct drm_connector_state *conn_state)
{
	WARN_ON(conn_state->connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK);

	if (!conn_state->writeback_job)
		conn_state->writeback_job =
			kzalloc(sizeof(*conn_state->writeback_job), GFP_KERNEL);

	return conn_state->writeback_job;
}