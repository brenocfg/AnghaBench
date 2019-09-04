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
typedef  int u64 ;
struct i40iw_sc_cqp {int /*<<< orphan*/  dev; scalar_t__ polarity; } ;
struct i40iw_sc_ceq {int elem_cnt; int ceq_elem_pa; int first_pm_pbl_idx; int ceq_id; scalar_t__ tph_en; scalar_t__ virtual_map; scalar_t__ pbl_chunk_size; scalar_t__ tph_val; TYPE_1__* dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {struct i40iw_sc_cqp* cqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_CEQ_LPBLSIZE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CEQ_VMAP ; 
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_TPHEN ; 
 int /*<<< orphan*/  I40IW_CQPSQ_TPHVAL ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 scalar_t__ I40IW_CQP_OP_CREATE_CEQ ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 int LS_64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_ceq_create(struct i40iw_sc_ceq *ceq,
						  u64 scratch,
						  bool post_sq)
{
	struct i40iw_sc_cqp *cqp;
	u64 *wqe;
	u64 header;

	cqp = ceq->dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	set_64bit_val(wqe, 16, ceq->elem_cnt);
	set_64bit_val(wqe, 32, (ceq->virtual_map ? 0 : ceq->ceq_elem_pa));
	set_64bit_val(wqe, 48, (ceq->virtual_map ? ceq->first_pm_pbl_idx : 0));
	set_64bit_val(wqe, 56, LS_64(ceq->tph_val, I40IW_CQPSQ_TPHVAL));

	header = ceq->ceq_id |
		 LS_64(I40IW_CQP_OP_CREATE_CEQ, I40IW_CQPSQ_OPCODE) |
		 LS_64(ceq->pbl_chunk_size, I40IW_CQPSQ_CEQ_LPBLSIZE) |
		 LS_64(ceq->virtual_map, I40IW_CQPSQ_CEQ_VMAP) |
		 LS_64(ceq->tph_en, I40IW_CQPSQ_TPHEN) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "CEQ_CREATE WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}