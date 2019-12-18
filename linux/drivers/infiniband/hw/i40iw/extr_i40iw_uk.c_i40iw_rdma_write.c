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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_5__ {int tag_off; int stag; } ;
struct i40iw_rdma_write {size_t num_lo_sges; TYPE_3__* lo_sg_list; TYPE_2__ rem_addr; } ;
struct i40iw_qp_uk {size_t max_sq_frag_cnt; int swqe_polarity; } ;
struct TYPE_4__ {struct i40iw_rdma_write rdma_write; } ;
struct i40iw_post_sq_info {int read_fence; int local_fence; int signaled; int /*<<< orphan*/  wr_id; TYPE_1__ op; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_6__ {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_ADDFRAGCNT ; 
 int /*<<< orphan*/  I40IWQPSQ_FRAG_TO ; 
 int /*<<< orphan*/  I40IWQPSQ_LOCALFENCE ; 
 int /*<<< orphan*/  I40IWQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IWQPSQ_READFENCE ; 
 int /*<<< orphan*/  I40IWQPSQ_REMSTAG ; 
 int /*<<< orphan*/  I40IWQPSQ_SIGCOMPL ; 
 int /*<<< orphan*/  I40IWQPSQ_VALID ; 
 int I40IWQP_OP_RDMA_WRITE ; 
 int I40IW_ERR_BAD_STAG ; 
 int I40IW_ERR_INVALID_FRAG_COUNT ; 
 int I40IW_ERR_QP_INVALID_MSG_SIZE ; 
 int I40IW_ERR_QP_TOOMANY_WRS_POSTED ; 
 size_t I40IW_MAX_OUTBOUND_MESSAGE_SIZE ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int i40iw_fragcnt_to_wqesize_sq (size_t,int /*<<< orphan*/ *) ; 
 int* i40iw_qp_get_next_send_wqe (struct i40iw_qp_uk*,size_t*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_qp_post_wr (struct i40iw_qp_uk*) ; 
 int /*<<< orphan*/  i40iw_set_fragment (int*,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static enum i40iw_status_code i40iw_rdma_write(struct i40iw_qp_uk *qp,
					       struct i40iw_post_sq_info *info,
					       bool post_sq)
{
	u64 header;
	u64 *wqe;
	struct i40iw_rdma_write *op_info;
	u32 i, wqe_idx;
	u32 total_size = 0, byte_off;
	enum i40iw_status_code ret_code;
	bool read_fence = false;
	u8 wqe_size;

	op_info = &info->op.rdma_write;
	if (op_info->num_lo_sges > qp->max_sq_frag_cnt)
		return I40IW_ERR_INVALID_FRAG_COUNT;

	for (i = 0; i < op_info->num_lo_sges; i++)
		total_size += op_info->lo_sg_list[i].len;

	if (total_size > I40IW_MAX_OUTBOUND_MESSAGE_SIZE)
		return I40IW_ERR_QP_INVALID_MSG_SIZE;

	read_fence |= info->read_fence;

	ret_code = i40iw_fragcnt_to_wqesize_sq(op_info->num_lo_sges, &wqe_size);
	if (ret_code)
		return ret_code;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, total_size, info->wr_id);
	if (!wqe)
		return I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	set_64bit_val(wqe, 16,
		      LS_64(op_info->rem_addr.tag_off, I40IWQPSQ_FRAG_TO));
	if (!op_info->rem_addr.stag)
		return I40IW_ERR_BAD_STAG;

	header = LS_64(op_info->rem_addr.stag, I40IWQPSQ_REMSTAG) |
		 LS_64(I40IWQP_OP_RDMA_WRITE, I40IWQPSQ_OPCODE) |
		 LS_64((op_info->num_lo_sges > 1 ?  (op_info->num_lo_sges - 1) : 0), I40IWQPSQ_ADDFRAGCNT) |
		 LS_64(read_fence, I40IWQPSQ_READFENCE) |
		 LS_64(info->local_fence, I40IWQPSQ_LOCALFENCE) |
		 LS_64(info->signaled, I40IWQPSQ_SIGCOMPL) |
		 LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	i40iw_set_fragment(wqe, 0, op_info->lo_sg_list);

	for (i = 1, byte_off = 32; i < op_info->num_lo_sges; i++) {
		i40iw_set_fragment(wqe, byte_off, &op_info->lo_sg_list[i]);
		byte_off += 16;
	}

	wmb(); /* make sure WQE is populated before valid bit is set */

	set_64bit_val(wqe, 24, header);

	if (post_sq)
		i40iw_qp_post_wr(qp);

	return 0;
}