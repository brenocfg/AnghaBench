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
typedef  scalar_t__ u32 ;
struct i40iw_sc_aeqe {int dummy; } ;
struct i40iw_sc_aeq {int size; int polarity; scalar_t__ elem_cnt; scalar_t__ first_pm_pbl_idx; scalar_t__ virtual_map; int /*<<< orphan*/  pbl_chunk_size; int /*<<< orphan*/ * pbl_list; int /*<<< orphan*/  aeq_ring; int /*<<< orphan*/  aeq_elem_pa; TYPE_3__* dev; struct i40iw_sc_aeqe* aeqe_base; } ;
struct i40iw_aeq_init_info {scalar_t__ elem_cnt; scalar_t__ first_pm_pbl_idx; TYPE_3__* dev; int /*<<< orphan*/  pbl_chunk_size; int /*<<< orphan*/ * pbl_list; scalar_t__ virtual_map; int /*<<< orphan*/  aeq_elem_pa; scalar_t__ aeqe_base; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_6__ {struct i40iw_sc_aeq* aeq; TYPE_2__* hmc_info; } ;
struct TYPE_5__ {TYPE_1__* hmc_obj; } ;
struct TYPE_4__ {scalar_t__ cnt; } ;

/* Variables and functions */
 int I40IW_ERR_INVALID_PBLE_INDEX ; 
 int I40IW_ERR_INVALID_SIZE ; 
 size_t I40IW_HMC_IW_PBLE ; 
 scalar_t__ I40IW_MAX_AEQ_ENTRIES ; 
 scalar_t__ I40IW_MIN_AEQ_ENTRIES ; 
 int /*<<< orphan*/  I40IW_RING_INIT (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_aeq_init(struct i40iw_sc_aeq *aeq,
						struct i40iw_aeq_init_info *info)
{
	u32 pble_obj_cnt;

	if ((info->elem_cnt < I40IW_MIN_AEQ_ENTRIES) ||
	    (info->elem_cnt > I40IW_MAX_AEQ_ENTRIES))
		return I40IW_ERR_INVALID_SIZE;
	pble_obj_cnt = info->dev->hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].cnt;

	if (info->virtual_map && (info->first_pm_pbl_idx >= pble_obj_cnt))
		return I40IW_ERR_INVALID_PBLE_INDEX;

	aeq->size = sizeof(*aeq);
	aeq->polarity = 1;
	aeq->aeqe_base = (struct i40iw_sc_aeqe *)info->aeqe_base;
	aeq->dev = info->dev;
	aeq->elem_cnt = info->elem_cnt;

	aeq->aeq_elem_pa = info->aeq_elem_pa;
	I40IW_RING_INIT(aeq->aeq_ring, aeq->elem_cnt);
	info->dev->aeq = aeq;

	aeq->virtual_map = info->virtual_map;
	aeq->pbl_list = (aeq->virtual_map ? info->pbl_list : NULL);
	aeq->pbl_chunk_size = (aeq->virtual_map ? info->pbl_chunk_size : 0);
	aeq->first_pm_pbl_idx = (aeq->virtual_map ? info->first_pm_pbl_idx : 0);
	info->dev->aeq = aeq;
	return 0;
}