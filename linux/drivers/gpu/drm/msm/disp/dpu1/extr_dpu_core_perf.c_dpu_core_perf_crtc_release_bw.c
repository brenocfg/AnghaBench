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
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_2__ base; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {scalar_t__ enable_bw_release; } ;
struct dpu_kms {TYPE_1__ perf; int /*<<< orphan*/  bandwidth_ref; int /*<<< orphan*/  catalog; } ;
struct dpu_crtc_state {int dummy; } ;
struct TYPE_6__ {scalar_t__ bw_ctl; } ;
struct dpu_crtc {TYPE_3__ cur_perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  _dpu_core_perf_crtc_update_bus (struct dpu_kms*,struct drm_crtc*) ; 
 struct dpu_kms* _dpu_crtc_get_kms (struct drm_crtc*) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 struct dpu_crtc_state* to_dpu_crtc_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_cmd_release_bw (int /*<<< orphan*/ ) ; 

void dpu_core_perf_crtc_release_bw(struct drm_crtc *crtc)
{
	struct dpu_crtc *dpu_crtc;
	struct dpu_crtc_state *dpu_cstate;
	struct dpu_kms *kms;

	if (!crtc) {
		DPU_ERROR("invalid crtc\n");
		return;
	}

	kms = _dpu_crtc_get_kms(crtc);
	if (!kms || !kms->catalog) {
		DPU_ERROR("invalid kms\n");
		return;
	}

	dpu_crtc = to_dpu_crtc(crtc);
	dpu_cstate = to_dpu_crtc_state(crtc->state);

	if (atomic_dec_return(&kms->bandwidth_ref) > 0)
		return;

	/* Release the bandwidth */
	if (kms->perf.enable_bw_release) {
		trace_dpu_cmd_release_bw(crtc->base.id);
		DPU_DEBUG("Release BW crtc=%d\n", crtc->base.id);
		dpu_crtc->cur_perf.bw_ctl = 0;
		_dpu_core_perf_crtc_update_bus(kms, crtc);
	}
}