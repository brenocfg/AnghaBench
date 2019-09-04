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
typedef  scalar_t__ u32 ;
struct dpu_vbif_set_ot_params {int /*<<< orphan*/  xin_id; scalar_t__ rd; } ;
struct TYPE_4__ {scalar_t__ (* get_limit_conf ) (struct dpu_hw_vbif*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct dpu_hw_vbif {scalar_t__ idx; TYPE_2__ ops; TYPE_1__* cap; } ;
struct TYPE_3__ {scalar_t__ default_ot_wr_limit; scalar_t__ default_ot_rd_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 scalar_t__ EINVAL ; 
 scalar_t__ VBIF_0 ; 
 int /*<<< orphan*/  _dpu_vbif_apply_dynamic_ot_limit (struct dpu_hw_vbif*,scalar_t__*,struct dpu_vbif_set_ot_params*) ; 
 scalar_t__ stub1 (struct dpu_hw_vbif*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 _dpu_vbif_get_ot_limit(struct dpu_hw_vbif *vbif,
	struct dpu_vbif_set_ot_params *params)
{
	u32 ot_lim = 0;
	u32 val;

	if (!vbif || !vbif->cap) {
		DPU_ERROR("invalid arguments vbif %d\n", vbif != 0);
		return -EINVAL;
	}

	if (vbif->cap->default_ot_wr_limit && !params->rd)
		ot_lim = vbif->cap->default_ot_wr_limit;
	else if (vbif->cap->default_ot_rd_limit && params->rd)
		ot_lim = vbif->cap->default_ot_rd_limit;

	/*
	 * If default ot is not set from dt/catalog,
	 * then do not configure it.
	 */
	if (ot_lim == 0)
		goto exit;

	/* Modify the limits if the target and the use case requires it */
	_dpu_vbif_apply_dynamic_ot_limit(vbif, &ot_lim, params);

	if (vbif && vbif->ops.get_limit_conf) {
		val = vbif->ops.get_limit_conf(vbif,
				params->xin_id, params->rd);
		if (val == ot_lim)
			ot_lim = 0;
	}

exit:
	DPU_DEBUG("vbif:%d xin:%d ot_lim:%d\n",
			vbif->idx - VBIF_0, params->xin_id, ot_lim);
	return ot_lim;
}