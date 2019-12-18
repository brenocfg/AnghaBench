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
typedef  int u32 ;
struct dpu_vbif_set_ot_params {scalar_t__ vbif_idx; int /*<<< orphan*/  clk_ctrl; int /*<<< orphan*/  xin_id; int /*<<< orphan*/  rd; int /*<<< orphan*/  num; } ;
struct dpu_kms {struct dpu_hw_vbif** hw_vbif; struct dpu_hw_mdp* hw_mdp; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_halt_ctrl ) (struct dpu_hw_vbif*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_limit_conf ) (struct dpu_hw_vbif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_write_gather_en ) (struct dpu_hw_vbif*,int /*<<< orphan*/ ) ;} ;
struct dpu_hw_vbif {scalar_t__ idx; TYPE_1__ ops; } ;
struct TYPE_4__ {int (* setup_clk_force_ctrl ) (struct dpu_hw_mdp*,int /*<<< orphan*/ ,int) ;} ;
struct dpu_hw_mdp {TYPE_2__ ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpu_hw_vbif**) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int _dpu_vbif_get_ot_limit (struct dpu_hw_vbif*,struct dpu_vbif_set_ot_params*) ; 
 int _dpu_vbif_wait_for_xin_halt (struct dpu_hw_vbif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_vbif*,int /*<<< orphan*/ ) ; 
 int stub2 (struct dpu_hw_mdp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct dpu_hw_vbif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct dpu_hw_vbif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct dpu_hw_vbif*,int /*<<< orphan*/ ,int) ; 
 int stub6 (struct dpu_hw_mdp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_dpu_perf_set_ot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  trace_dpu_vbif_wait_xin_halt_fail (scalar_t__,int /*<<< orphan*/ ) ; 

void dpu_vbif_set_ot_limit(struct dpu_kms *dpu_kms,
		struct dpu_vbif_set_ot_params *params)
{
	struct dpu_hw_vbif *vbif = NULL;
	struct dpu_hw_mdp *mdp;
	bool forced_on = false;
	u32 ot_lim;
	int ret, i;

	if (!dpu_kms) {
		DPU_ERROR("invalid arguments\n");
		return;
	}
	mdp = dpu_kms->hw_mdp;

	for (i = 0; i < ARRAY_SIZE(dpu_kms->hw_vbif); i++) {
		if (dpu_kms->hw_vbif[i] &&
				dpu_kms->hw_vbif[i]->idx == params->vbif_idx)
			vbif = dpu_kms->hw_vbif[i];
	}

	if (!vbif || !mdp) {
		DPU_DEBUG("invalid arguments vbif %d mdp %d\n",
				vbif != 0, mdp != 0);
		return;
	}

	if (!mdp->ops.setup_clk_force_ctrl ||
			!vbif->ops.set_limit_conf ||
			!vbif->ops.set_halt_ctrl)
		return;

	/* set write_gather_en for all write clients */
	if (vbif->ops.set_write_gather_en && !params->rd)
		vbif->ops.set_write_gather_en(vbif, params->xin_id);

	ot_lim = _dpu_vbif_get_ot_limit(vbif, params) & 0xFF;

	if (ot_lim == 0)
		return;

	trace_dpu_perf_set_ot(params->num, params->xin_id, ot_lim,
		params->vbif_idx);

	forced_on = mdp->ops.setup_clk_force_ctrl(mdp, params->clk_ctrl, true);

	vbif->ops.set_limit_conf(vbif, params->xin_id, params->rd, ot_lim);

	vbif->ops.set_halt_ctrl(vbif, params->xin_id, true);

	ret = _dpu_vbif_wait_for_xin_halt(vbif, params->xin_id);
	if (ret)
		trace_dpu_vbif_wait_xin_halt_fail(vbif->idx, params->xin_id);

	vbif->ops.set_halt_ctrl(vbif, params->xin_id, false);

	if (forced_on)
		mdp->ops.setup_clk_force_ctrl(mdp, params->clk_ctrl, false);
}