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
typedef  scalar_t__ u32 ;
struct TYPE_7__ {scalar_t__ cq_size; int polarity; int /*<<< orphan*/ * cqe_alloc_reg; int /*<<< orphan*/  avoid_mem_cflct; scalar_t__ cq_id; int /*<<< orphan*/  cq_ring; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  cq_base; } ;
struct i40iw_sc_cq {scalar_t__ ceq_id; scalar_t__ first_pm_pbl_idx; TYPE_3__ cq_uk; int /*<<< orphan*/  pbl_chunk_size; scalar_t__ virtual_map; int /*<<< orphan*/  pbl_list; int /*<<< orphan*/  tph_val; int /*<<< orphan*/  tph_en; int /*<<< orphan*/  ceq_id_valid; int /*<<< orphan*/  ceqe_mask; int /*<<< orphan*/  cq_type; TYPE_4__* dev; int /*<<< orphan*/  shadow_read_threshold; int /*<<< orphan*/  shadow_area_pa; int /*<<< orphan*/  cq_pa; } ;
struct i40iw_ccq_init_info {scalar_t__ num_elem; scalar_t__ ceq_id; scalar_t__ first_pm_pbl_idx; TYPE_4__* dev; int /*<<< orphan*/  pbl_chunk_size; scalar_t__ virtual_map; int /*<<< orphan*/  pbl_list; int /*<<< orphan*/  avoid_mem_cflct; int /*<<< orphan*/  tph_val; int /*<<< orphan*/  tph_en; int /*<<< orphan*/  ceq_id_valid; int /*<<< orphan*/  ceqe_mask; int /*<<< orphan*/  shadow_read_threshold; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  shadow_area_pa; int /*<<< orphan*/  cq_base; int /*<<< orphan*/  cq_pa; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_8__ {struct i40iw_sc_cq* ccq; TYPE_2__* hmc_info; } ;
struct TYPE_6__ {TYPE_1__* hmc_obj; } ;
struct TYPE_5__ {scalar_t__ cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQ_TYPE_CQP ; 
 int I40IW_ERR_INVALID_CEQ_ID ; 
 int I40IW_ERR_INVALID_PBLE_INDEX ; 
 int I40IW_ERR_INVALID_SIZE ; 
 size_t I40IW_HMC_IW_PBLE ; 
 scalar_t__ I40IW_MAX_CEQID ; 
 scalar_t__ I40IW_MAX_CQ_SIZE ; 
 scalar_t__ I40IW_MIN_CQ_SIZE ; 
 int /*<<< orphan*/  I40IW_RING_INIT (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_ccq_init(struct i40iw_sc_cq *cq,
						struct i40iw_ccq_init_info *info)
{
	u32 pble_obj_cnt;

	if (info->num_elem < I40IW_MIN_CQ_SIZE || info->num_elem > I40IW_MAX_CQ_SIZE)
		return I40IW_ERR_INVALID_SIZE;

	if (info->ceq_id > I40IW_MAX_CEQID)
		return I40IW_ERR_INVALID_CEQ_ID;

	pble_obj_cnt = info->dev->hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].cnt;

	if (info->virtual_map && (info->first_pm_pbl_idx >= pble_obj_cnt))
		return I40IW_ERR_INVALID_PBLE_INDEX;

	cq->cq_pa = info->cq_pa;
	cq->cq_uk.cq_base = info->cq_base;
	cq->shadow_area_pa = info->shadow_area_pa;
	cq->cq_uk.shadow_area = info->shadow_area;
	cq->shadow_read_threshold = info->shadow_read_threshold;
	cq->dev = info->dev;
	cq->ceq_id = info->ceq_id;
	cq->cq_uk.cq_size = info->num_elem;
	cq->cq_type = I40IW_CQ_TYPE_CQP;
	cq->ceqe_mask = info->ceqe_mask;
	I40IW_RING_INIT(cq->cq_uk.cq_ring, info->num_elem);

	cq->cq_uk.cq_id = 0;    /* control cq is id 0 always */
	cq->ceq_id_valid = info->ceq_id_valid;
	cq->tph_en = info->tph_en;
	cq->tph_val = info->tph_val;
	cq->cq_uk.avoid_mem_cflct = info->avoid_mem_cflct;

	cq->pbl_list = info->pbl_list;
	cq->virtual_map = info->virtual_map;
	cq->pbl_chunk_size = info->pbl_chunk_size;
	cq->first_pm_pbl_idx = info->first_pm_pbl_idx;
	cq->cq_uk.polarity = true;

	/* following are only for iw cqs so initialize them to zero */
	cq->cq_uk.cqe_alloc_reg = NULL;
	info->dev->ccq = cq;
	return 0;
}