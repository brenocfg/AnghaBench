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
struct msm_display_topology {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_2__ base; } ;
struct drm_crtc_state {TYPE_4__* crtc; } ;
struct drm_connector_state {TYPE_5__* connector; } ;
struct dpu_rm_rsvp {int /*<<< orphan*/  enc_id; int /*<<< orphan*/  seq; } ;
struct dpu_rm_requirements {int dummy; } ;
struct dpu_rm {int /*<<< orphan*/  rm_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DPU_RM_STAGE_AFTER_CLEAR ; 
 int /*<<< orphan*/  DPU_RM_STAGE_AFTER_RSVPNEXT ; 
 int /*<<< orphan*/  DPU_RM_STAGE_BEGIN ; 
 int /*<<< orphan*/  DPU_RM_STAGE_FINAL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RM_RQ_CLEAR (struct dpu_rm_requirements*) ; 
 scalar_t__ RM_RQ_LOCK (struct dpu_rm_requirements*) ; 
 int _dpu_rm_commit_rsvp (struct dpu_rm*,struct dpu_rm_rsvp*,struct drm_connector_state*) ; 
 struct dpu_rm_rsvp* _dpu_rm_get_rsvp (struct dpu_rm*,struct drm_encoder*) ; 
 int _dpu_rm_make_next_rsvp (struct dpu_rm*,struct drm_encoder*,struct drm_crtc_state*,struct drm_connector_state*,struct dpu_rm_rsvp*,struct dpu_rm_requirements*) ; 
 int _dpu_rm_populate_requirements (struct dpu_rm*,struct drm_encoder*,struct drm_crtc_state*,struct drm_connector_state*,struct dpu_rm_requirements*,struct msm_display_topology) ; 
 int /*<<< orphan*/  _dpu_rm_print_rsvps (struct dpu_rm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dpu_rm_release_rsvp (struct dpu_rm*,struct dpu_rm_rsvp*,TYPE_5__*) ; 
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 struct dpu_rm_rsvp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dpu_rm_reserve(
		struct dpu_rm *rm,
		struct drm_encoder *enc,
		struct drm_crtc_state *crtc_state,
		struct drm_connector_state *conn_state,
		struct msm_display_topology topology,
		bool test_only)
{
	struct dpu_rm_rsvp *rsvp_cur, *rsvp_nxt;
	struct dpu_rm_requirements reqs;
	int ret;

	if (!rm || !enc || !crtc_state || !conn_state) {
		DPU_ERROR("invalid arguments\n");
		return -EINVAL;
	}

	/* Check if this is just a page-flip */
	if (!drm_atomic_crtc_needs_modeset(crtc_state))
		return 0;

	DRM_DEBUG_KMS("reserving hw for conn %d enc %d crtc %d test_only %d\n",
		      conn_state->connector->base.id, enc->base.id,
		      crtc_state->crtc->base.id, test_only);

	mutex_lock(&rm->rm_lock);

	_dpu_rm_print_rsvps(rm, DPU_RM_STAGE_BEGIN);

	ret = _dpu_rm_populate_requirements(rm, enc, crtc_state,
			conn_state, &reqs, topology);
	if (ret) {
		DPU_ERROR("failed to populate hw requirements\n");
		goto end;
	}

	/*
	 * We only support one active reservation per-hw-block. But to implement
	 * transactional semantics for test-only, and for allowing failure while
	 * modifying your existing reservation, over the course of this
	 * function we can have two reservations:
	 * Current: Existing reservation
	 * Next: Proposed reservation. The proposed reservation may fail, or may
	 *       be discarded if in test-only mode.
	 * If reservation is successful, and we're not in test-only, then we
	 * replace the current with the next.
	 */
	rsvp_nxt = kzalloc(sizeof(*rsvp_nxt), GFP_KERNEL);
	if (!rsvp_nxt) {
		ret = -ENOMEM;
		goto end;
	}

	rsvp_cur = _dpu_rm_get_rsvp(rm, enc);

	/*
	 * User can request that we clear out any reservation during the
	 * atomic_check phase by using this CLEAR bit
	 */
	if (rsvp_cur && test_only && RM_RQ_CLEAR(&reqs)) {
		DPU_DEBUG("test_only & CLEAR: clear rsvp[s%de%d]\n",
				rsvp_cur->seq, rsvp_cur->enc_id);
		_dpu_rm_release_rsvp(rm, rsvp_cur, conn_state->connector);
		rsvp_cur = NULL;
		_dpu_rm_print_rsvps(rm, DPU_RM_STAGE_AFTER_CLEAR);
	}

	/* Check the proposed reservation, store it in hw's "next" field */
	ret = _dpu_rm_make_next_rsvp(rm, enc, crtc_state, conn_state,
			rsvp_nxt, &reqs);

	_dpu_rm_print_rsvps(rm, DPU_RM_STAGE_AFTER_RSVPNEXT);

	if (ret) {
		DPU_ERROR("failed to reserve hw resources: %d\n", ret);
		_dpu_rm_release_rsvp(rm, rsvp_nxt, conn_state->connector);
	} else if (test_only && !RM_RQ_LOCK(&reqs)) {
		/*
		 * Normally, if test_only, test the reservation and then undo
		 * However, if the user requests LOCK, then keep the reservation
		 * made during the atomic_check phase.
		 */
		DPU_DEBUG("test_only: discard test rsvp[s%de%d]\n",
				rsvp_nxt->seq, rsvp_nxt->enc_id);
		_dpu_rm_release_rsvp(rm, rsvp_nxt, conn_state->connector);
	} else {
		if (test_only && RM_RQ_LOCK(&reqs))
			DPU_DEBUG("test_only & LOCK: lock rsvp[s%de%d]\n",
					rsvp_nxt->seq, rsvp_nxt->enc_id);

		_dpu_rm_release_rsvp(rm, rsvp_cur, conn_state->connector);

		ret = _dpu_rm_commit_rsvp(rm, rsvp_nxt, conn_state);
	}

	_dpu_rm_print_rsvps(rm, DPU_RM_STAGE_FINAL);

end:
	mutex_unlock(&rm->rm_lock);

	return ret;
}