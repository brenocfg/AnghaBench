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
typedef  int /*<<< orphan*/  topology ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;
struct dpu_rm_topology_def {int needs_split_display; int /*<<< orphan*/  top_name; } ;
struct dpu_rm_rsvp {int /*<<< orphan*/  list; int /*<<< orphan*/  topology; int /*<<< orphan*/  enc_id; scalar_t__ seq; } ;
struct dpu_rm_requirements {int /*<<< orphan*/  hw_res; struct dpu_rm_topology_def* topology; } ;
struct dpu_rm {int /*<<< orphan*/  rsvps; scalar_t__ rsvp_next_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  _dpu_rm_reserve_ctls (struct dpu_rm*,struct dpu_rm_rsvp*,struct dpu_rm_topology_def*) ; 
 int _dpu_rm_reserve_intf_related_hw (struct dpu_rm*,struct dpu_rm_rsvp*,int /*<<< orphan*/ *) ; 
 int _dpu_rm_reserve_lms (struct dpu_rm*,struct dpu_rm_rsvp*,struct dpu_rm_requirements*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct dpu_rm_topology_def*,struct dpu_rm_topology_def*,int) ; 

__attribute__((used)) static int _dpu_rm_make_next_rsvp(
		struct dpu_rm *rm,
		struct drm_encoder *enc,
		struct drm_crtc_state *crtc_state,
		struct drm_connector_state *conn_state,
		struct dpu_rm_rsvp *rsvp,
		struct dpu_rm_requirements *reqs)
{
	int ret;
	struct dpu_rm_topology_def topology;

	/* Create reservation info, tag reserved blocks with it as we go */
	rsvp->seq = ++rm->rsvp_next_seq;
	rsvp->enc_id = enc->base.id;
	rsvp->topology = reqs->topology->top_name;
	list_add_tail(&rsvp->list, &rm->rsvps);

	ret = _dpu_rm_reserve_lms(rm, rsvp, reqs);
	if (ret) {
		DPU_ERROR("unable to find appropriate mixers\n");
		return ret;
	}

	/*
	 * Do assignment preferring to give away low-resource CTLs first:
	 * - Check mixers without Split Display
	 * - Only then allow to grab from CTLs with split display capability
	 */
	_dpu_rm_reserve_ctls(rm, rsvp, reqs->topology);
	if (ret && !reqs->topology->needs_split_display) {
		memcpy(&topology, reqs->topology, sizeof(topology));
		topology.needs_split_display = true;
		_dpu_rm_reserve_ctls(rm, rsvp, &topology);
	}
	if (ret) {
		DPU_ERROR("unable to find appropriate CTL\n");
		return ret;
	}

	/* Assign INTFs and blks whose usage is tied to them: CTL & CDM */
	ret = _dpu_rm_reserve_intf_related_hw(rm, rsvp, &reqs->hw_res);
	if (ret)
		return ret;

	return ret;
}