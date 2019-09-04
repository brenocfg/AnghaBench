#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_writeback_job {scalar_t__ fb; scalar_t__ out_fence; } ;
struct drm_crtc_state {int /*<<< orphan*/  active; } ;
struct drm_connector_state {TYPE_3__* crtc; int /*<<< orphan*/  state; struct drm_writeback_job* writeback_job; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_connector {scalar_t__ connector_type; int /*<<< orphan*/  name; TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ DRM_MODE_CONNECTOR_WRITEBACK ; 
 int EINVAL ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int drm_atomic_connector_check(struct drm_connector *connector,
		struct drm_connector_state *state)
{
	struct drm_crtc_state *crtc_state;
	struct drm_writeback_job *writeback_job = state->writeback_job;

	if ((connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK) || !writeback_job)
		return 0;

	if (writeback_job->fb && !state->crtc) {
		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] framebuffer without CRTC\n",
				 connector->base.id, connector->name);
		return -EINVAL;
	}

	if (state->crtc)
		crtc_state = drm_atomic_get_existing_crtc_state(state->state,
								state->crtc);

	if (writeback_job->fb && !crtc_state->active) {
		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] has framebuffer, but [CRTC:%d] is off\n",
				 connector->base.id, connector->name,
				 state->crtc->base.id);
		return -EINVAL;
	}

	if (writeback_job->out_fence && !writeback_job->fb) {
		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] requesting out-fence without framebuffer\n",
				 connector->base.id, connector->name);
		return -EINVAL;
	}

	return 0;
}