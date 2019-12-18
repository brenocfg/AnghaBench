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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct i40iw_sc_cqp {int polarity; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {scalar_t__ cq_size; scalar_t__ cq_id; int avoid_mem_cflct; } ;
struct i40iw_sc_cq {scalar_t__ cq_pa; scalar_t__ first_pm_pbl_idx; int ceq_id_valid; scalar_t__ ceq_id; int virtual_map; int pbl_chunk_size; int check_overflow; scalar_t__ shadow_area_pa; int tph_val; int ceqe_mask; int tph_en; TYPE_4__ cq_uk; int /*<<< orphan*/  pbl_list; TYPE_3__* dev; } ;
struct i40iw_modify_cq_info {scalar_t__ ceq_id; int cq_resize; int virtual_map; scalar_t__ first_pm_pbl_idx; scalar_t__ cq_pa; scalar_t__ cq_size; int pbl_chunk_size; int check_overflow; int shadow_read_threshold; scalar_t__ check_overflow_change; scalar_t__ ceq_change; int /*<<< orphan*/  pbl_list; scalar_t__ ceq_valid; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_7__ {struct i40iw_sc_cqp* cqp; TYPE_2__* hmc_info; } ;
struct TYPE_6__ {TYPE_1__* hmc_obj; } ;
struct TYPE_5__ {scalar_t__ cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_AVOIDMEMCNFLCT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CEQID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CEQIDVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CHKOVERFLOW ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CQRESIZE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_ENCEQEMASK ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_LPBLSIZE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_SHADOW_READ_THRESHOLD ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_VIRTMAP ; 
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_TPHEN ; 
 int /*<<< orphan*/  I40IW_CQPSQ_TPHVAL ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int I40IW_CQP_OP_MODIFY_CQ ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_INVALID_CEQ_ID ; 
 int I40IW_ERR_INVALID_PBLE_INDEX ; 
 int I40IW_ERR_RING_FULL ; 
 size_t I40IW_HMC_IW_PBLE ; 
 scalar_t__ I40IW_MAX_CEQID ; 
 scalar_t__ LS_64 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ RS_64_1 (struct i40iw_sc_cq*,int) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (scalar_t__*,scalar_t__) ; 
 scalar_t__* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,scalar_t__) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (scalar_t__*,int,scalar_t__) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_cq_modify(struct i40iw_sc_cq *cq,
						 struct i40iw_modify_cq_info *info,
						 u64 scratch,
						 bool post_sq)
{
	struct i40iw_sc_cqp *cqp;
	u64 *wqe;
	u64 header;
	u32 cq_size, ceq_id, first_pm_pbl_idx;
	u8 pbl_chunk_size;
	bool virtual_map, ceq_id_valid, check_overflow;
	u32 pble_obj_cnt;

	if (info->ceq_valid && (info->ceq_id > I40IW_MAX_CEQID))
		return I40IW_ERR_INVALID_CEQ_ID;

	pble_obj_cnt = cq->dev->hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].cnt;

	if (info->cq_resize && info->virtual_map &&
	    (info->first_pm_pbl_idx >= pble_obj_cnt))
		return I40IW_ERR_INVALID_PBLE_INDEX;

	cqp = cq->dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;

	cq->pbl_list = info->pbl_list;
	cq->cq_pa = info->cq_pa;
	cq->first_pm_pbl_idx = info->first_pm_pbl_idx;

	cq_size = info->cq_resize ? info->cq_size : cq->cq_uk.cq_size;
	if (info->ceq_change) {
		ceq_id_valid = true;
		ceq_id = info->ceq_id;
	} else {
		ceq_id_valid = cq->ceq_id_valid;
		ceq_id = ceq_id_valid ? cq->ceq_id : 0;
	}
	virtual_map = info->cq_resize ? info->virtual_map : cq->virtual_map;
	first_pm_pbl_idx = (info->cq_resize ?
			    (info->virtual_map ? info->first_pm_pbl_idx : 0) :
			    (cq->virtual_map ? cq->first_pm_pbl_idx : 0));
	pbl_chunk_size = (info->cq_resize ?
			  (info->virtual_map ? info->pbl_chunk_size : 0) :
			  (cq->virtual_map ? cq->pbl_chunk_size : 0));
	check_overflow = info->check_overflow_change ? info->check_overflow :
			 cq->check_overflow;
	cq->cq_uk.cq_size = cq_size;
	cq->ceq_id_valid = ceq_id_valid;
	cq->ceq_id = ceq_id;
	cq->virtual_map = virtual_map;
	cq->first_pm_pbl_idx = first_pm_pbl_idx;
	cq->pbl_chunk_size = pbl_chunk_size;
	cq->check_overflow = check_overflow;

	set_64bit_val(wqe, 0, cq_size);
	set_64bit_val(wqe, 8, RS_64_1(cq, 1));
	set_64bit_val(wqe, 16,
		      LS_64(info->shadow_read_threshold, I40IW_CQPSQ_CQ_SHADOW_READ_THRESHOLD));
	set_64bit_val(wqe, 32, (cq->virtual_map ? 0 : cq->cq_pa));
	set_64bit_val(wqe, 40, cq->shadow_area_pa);
	set_64bit_val(wqe, 48, (cq->virtual_map ? first_pm_pbl_idx : 0));
	set_64bit_val(wqe, 56, LS_64(cq->tph_val, I40IW_CQPSQ_TPHVAL));

	header = cq->cq_uk.cq_id |
		 LS_64(ceq_id, I40IW_CQPSQ_CQ_CEQID) |
		 LS_64(I40IW_CQP_OP_MODIFY_CQ, I40IW_CQPSQ_OPCODE) |
		 LS_64(info->cq_resize, I40IW_CQPSQ_CQ_CQRESIZE) |
		 LS_64(pbl_chunk_size, I40IW_CQPSQ_CQ_LPBLSIZE) |
		 LS_64(check_overflow, I40IW_CQPSQ_CQ_CHKOVERFLOW) |
		 LS_64(virtual_map, I40IW_CQPSQ_CQ_VIRTMAP) |
		 LS_64(cq->ceqe_mask, I40IW_CQPSQ_CQ_ENCEQEMASK) |
		 LS_64(ceq_id_valid, I40IW_CQPSQ_CQ_CEQIDVALID) |
		 LS_64(cq->tph_en, I40IW_CQPSQ_TPHEN) |
		 LS_64(cq->cq_uk.avoid_mem_cflct, I40IW_CQPSQ_CQ_AVOIDMEMCNFLCT) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "CQ_MODIFY WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}