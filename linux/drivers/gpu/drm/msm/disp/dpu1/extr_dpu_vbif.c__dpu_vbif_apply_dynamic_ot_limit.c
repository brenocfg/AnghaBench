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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct dpu_vbif_set_ot_params {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  xin_id; scalar_t__ rd; int /*<<< orphan*/  is_wfd; } ;
struct dpu_vbif_dynamic_ot_tbl {size_t count; TYPE_2__* cfg; } ;
struct dpu_hw_vbif {scalar_t__ idx; TYPE_1__* cap; } ;
struct TYPE_4__ {size_t ot_limit; int /*<<< orphan*/  pps; } ;
struct TYPE_3__ {int features; struct dpu_vbif_dynamic_ot_tbl dynamic_ot_wr_tbl; struct dpu_vbif_dynamic_ot_tbl dynamic_ot_rd_tbl; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  DPU_VBIF_QOS_OTLIM ; 
 scalar_t__ VBIF_0 ; 

__attribute__((used)) static void _dpu_vbif_apply_dynamic_ot_limit(struct dpu_hw_vbif *vbif,
		u32 *ot_lim, struct dpu_vbif_set_ot_params *params)
{
	u64 pps;
	const struct dpu_vbif_dynamic_ot_tbl *tbl;
	u32 i;

	if (!vbif || !(vbif->cap->features & BIT(DPU_VBIF_QOS_OTLIM)))
		return;

	/* Dynamic OT setting done only for WFD */
	if (!params->is_wfd)
		return;

	pps = params->frame_rate;
	pps *= params->width;
	pps *= params->height;

	tbl = params->rd ? &vbif->cap->dynamic_ot_rd_tbl :
			&vbif->cap->dynamic_ot_wr_tbl;

	for (i = 0; i < tbl->count; i++) {
		if (pps <= tbl->cfg[i].pps) {
			*ot_lim = tbl->cfg[i].ot_limit;
			break;
		}
	}

	DPU_DEBUG("vbif:%d xin:%d w:%d h:%d fps:%d pps:%llu ot:%u\n",
			vbif->idx - VBIF_0, params->xin_id,
			params->width, params->height, params->frame_rate,
			pps, *ot_lim);
}