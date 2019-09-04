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
typedef  int u64 ;
struct i40iw_sc_cqp {int polarity; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int cq_id; int avoid_mem_cflct; int /*<<< orphan*/  cq_size; } ;
struct i40iw_sc_cq {int virtual_map; int ceq_id_valid; int ceq_id; int pbl_chunk_size; int ceqe_mask; int tph_en; TYPE_2__ cq_uk; int /*<<< orphan*/  first_pm_pbl_idx; int /*<<< orphan*/  shadow_area_pa; TYPE_1__* dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_3__ {struct i40iw_sc_cqp* cqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_AVOIDMEMCNFLCT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CEQID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CEQIDVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_ENCEQEMASK ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_LPBLSIZE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_VIRTMAP ; 
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_TPHEN ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int I40IW_CQP_OP_DESTROY_CQ ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RS_64_1 (struct i40iw_sc_cq*,int) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_cq_destroy(struct i40iw_sc_cq *cq,
						  u64 scratch,
						  bool post_sq)
{
	struct i40iw_sc_cqp *cqp;
	u64 *wqe;
	u64 header;

	cqp = cq->dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	set_64bit_val(wqe, 0, cq->cq_uk.cq_size);
	set_64bit_val(wqe, 8, RS_64_1(cq, 1));
	set_64bit_val(wqe, 40, cq->shadow_area_pa);
	set_64bit_val(wqe, 48, (cq->virtual_map ? cq->first_pm_pbl_idx : 0));

	header = cq->cq_uk.cq_id |
		 LS_64((cq->ceq_id_valid ? cq->ceq_id : 0), I40IW_CQPSQ_CQ_CEQID) |
		 LS_64(I40IW_CQP_OP_DESTROY_CQ, I40IW_CQPSQ_OPCODE) |
		 LS_64(cq->pbl_chunk_size, I40IW_CQPSQ_CQ_LPBLSIZE) |
		 LS_64(cq->virtual_map, I40IW_CQPSQ_CQ_VIRTMAP) |
		 LS_64(cq->ceqe_mask, I40IW_CQPSQ_CQ_ENCEQEMASK) |
		 LS_64(cq->ceq_id_valid, I40IW_CQPSQ_CQ_CEQIDVALID) |
		 LS_64(cq->tph_en, I40IW_CQPSQ_TPHEN) |
		 LS_64(cq->cq_uk.avoid_mem_cflct, I40IW_CQPSQ_CQ_AVOIDMEMCNFLCT) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "CQ_DESTROY WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}