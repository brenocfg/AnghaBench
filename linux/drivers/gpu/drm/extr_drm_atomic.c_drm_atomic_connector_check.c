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
struct drm_writeback_job {scalar_t__ out_fence; scalar_t__ fb; } ;
struct drm_display_info {int bpc; } ;
struct drm_crtc_state {int /*<<< orphan*/  active; } ;
struct drm_connector_state {int max_bpc; struct drm_writeback_job* writeback_job; TYPE_3__* crtc; int /*<<< orphan*/  state; int /*<<< orphan*/  max_requested_bpc; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_connector {scalar_t__ connector_type; int /*<<< orphan*/  name; TYPE_2__ base; scalar_t__ max_bpc_property; struct drm_display_info display_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ DRM_MODE_CONNECTOR_WRITEBACK ; 
 int EINVAL ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  drm_writeback_cleanup_job (struct drm_writeback_job*) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_atomic_connector_check(struct drm_connector *connector,
		struct drm_connector_state *state)
{
	struct drm_crtc_state *crtc_state;
	struct drm_writeback_job *writeback_job = state->writeback_job;
	const struct drm_display_info *info = &connector->display_info;

	state->max_bpc = info->bpc ? info->bpc : 8;
	if (connector->max_bpc_property)
		state->max_bpc = min(state->max_bpc, state->max_requested_bpc);

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

	if (!writeback_job->fb) {
		if (writeback_job->out_fence) {
			DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] requesting out-fence without framebuffer\n",
					 connector->base.id, connector->name);
			return -EINVAL;
		}

		drm_writeback_cleanup_job(writeback_job);
		state->writeback_job = NULL;
	}

	return 0;
}