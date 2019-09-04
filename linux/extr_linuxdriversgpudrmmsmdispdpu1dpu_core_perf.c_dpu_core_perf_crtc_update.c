#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct msm_drm_private {int dummy; } ;
struct TYPE_5__ {int id; } ;
struct drm_crtc {TYPE_1__ base; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int core_clk_rate; TYPE_2__* core_clk; } ;
struct dpu_kms {TYPE_3__ perf; TYPE_4__* dev; int /*<<< orphan*/  catalog; } ;
struct dpu_core_perf_params {scalar_t__* bw_ctl; scalar_t__* max_per_pipe_ib; scalar_t__ core_clk_rate; } ;
struct dpu_crtc_state {struct dpu_core_perf_params new_perf; } ;
struct dpu_crtc {struct dpu_core_perf_params cur_perf; } ;
struct TYPE_8__ {struct msm_drm_private* dev_private; } ;
struct TYPE_6__ {int clk_name; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 size_t DPU_POWER_HANDLE_DBUS_ID_EBI ; 
 size_t DPU_POWER_HANDLE_DBUS_ID_LLCC ; 
 int DPU_POWER_HANDLE_DBUS_ID_MAX ; 
 size_t DPU_POWER_HANDLE_DBUS_ID_MNOC ; 
 int EINVAL ; 
 scalar_t__ _dpu_core_perf_crtc_is_power_on (struct drm_crtc*) ; 
 int _dpu_core_perf_crtc_update_bus (struct dpu_kms*,struct drm_crtc*,int) ; 
 int _dpu_core_perf_get_core_clk_rate (struct dpu_kms*) ; 
 int _dpu_core_perf_set_core_clk_rate (struct dpu_kms*,int) ; 
 struct dpu_kms* _dpu_crtc_get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  memset (struct dpu_core_perf_params*,int /*<<< orphan*/ ,int) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 struct dpu_crtc_state* to_dpu_crtc_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_core_perf_update_clk (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  trace_dpu_perf_crtc_update (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int) ; 

int dpu_core_perf_crtc_update(struct drm_crtc *crtc,
		int params_changed, bool stop_req)
{
	struct dpu_core_perf_params *new, *old;
	int update_bus = 0, update_clk = 0;
	u64 clk_rate = 0;
	struct dpu_crtc *dpu_crtc;
	struct dpu_crtc_state *dpu_cstate;
	int i;
	struct msm_drm_private *priv;
	struct dpu_kms *kms;
	int ret;

	if (!crtc) {
		DPU_ERROR("invalid crtc\n");
		return -EINVAL;
	}

	kms = _dpu_crtc_get_kms(crtc);
	if (!kms || !kms->catalog) {
		DPU_ERROR("invalid kms\n");
		return -EINVAL;
	}
	priv = kms->dev->dev_private;

	dpu_crtc = to_dpu_crtc(crtc);
	dpu_cstate = to_dpu_crtc_state(crtc->state);

	DPU_DEBUG("crtc:%d stop_req:%d core_clk:%llu\n",
			crtc->base.id, stop_req, kms->perf.core_clk_rate);

	old = &dpu_crtc->cur_perf;
	new = &dpu_cstate->new_perf;

	if (_dpu_core_perf_crtc_is_power_on(crtc) && !stop_req) {
		for (i = 0; i < DPU_POWER_HANDLE_DBUS_ID_MAX; i++) {
			/*
			 * cases for bus bandwidth update.
			 * 1. new bandwidth vote - "ab or ib vote" is higher
			 *    than current vote for update request.
			 * 2. new bandwidth vote - "ab or ib vote" is lower
			 *    than current vote at end of commit or stop.
			 */
			if ((params_changed && ((new->bw_ctl[i] >
						old->bw_ctl[i]) ||
				  (new->max_per_pipe_ib[i] >
						old->max_per_pipe_ib[i]))) ||
			    (!params_changed && ((new->bw_ctl[i] <
						old->bw_ctl[i]) ||
				  (new->max_per_pipe_ib[i] <
						old->max_per_pipe_ib[i])))) {
				DPU_DEBUG(
					"crtc=%d p=%d new_bw=%llu,old_bw=%llu\n",
					crtc->base.id, params_changed,
					new->bw_ctl[i], old->bw_ctl[i]);
				old->bw_ctl[i] = new->bw_ctl[i];
				old->max_per_pipe_ib[i] =
						new->max_per_pipe_ib[i];
				update_bus |= BIT(i);
			}
		}

		if ((params_changed &&
				(new->core_clk_rate > old->core_clk_rate)) ||
				(!params_changed &&
				(new->core_clk_rate < old->core_clk_rate))) {
			old->core_clk_rate = new->core_clk_rate;
			update_clk = 1;
		}
	} else {
		DPU_DEBUG("crtc=%d disable\n", crtc->base.id);
		memset(old, 0, sizeof(*old));
		memset(new, 0, sizeof(*new));
		update_bus = ~0;
		update_clk = 1;
	}
	trace_dpu_perf_crtc_update(crtc->base.id,
				new->bw_ctl[DPU_POWER_HANDLE_DBUS_ID_MNOC],
				new->bw_ctl[DPU_POWER_HANDLE_DBUS_ID_LLCC],
				new->bw_ctl[DPU_POWER_HANDLE_DBUS_ID_EBI],
				new->core_clk_rate, stop_req,
				update_bus, update_clk);

	for (i = 0; i < DPU_POWER_HANDLE_DBUS_ID_MAX; i++) {
		if (update_bus & BIT(i)) {
			ret = _dpu_core_perf_crtc_update_bus(kms, crtc, i);
			if (ret) {
				DPU_ERROR("crtc-%d: failed to update bw vote for bus-%d\n",
					  crtc->base.id, i);
				return ret;
			}
		}
	}

	/*
	 * Update the clock after bandwidth vote to ensure
	 * bandwidth is available before clock rate is increased.
	 */
	if (update_clk) {
		clk_rate = _dpu_core_perf_get_core_clk_rate(kms);

		trace_dpu_core_perf_update_clk(kms->dev, stop_req, clk_rate);

		ret = _dpu_core_perf_set_core_clk_rate(kms, clk_rate);
		if (ret) {
			DPU_ERROR("failed to set %s clock rate %llu\n",
					kms->perf.core_clk->clk_name, clk_rate);
			return ret;
		}

		kms->perf.core_clk_rate = clk_rate;
		DPU_DEBUG("update clk rate = %lld HZ\n", clk_rate);
	}
	return 0;
}