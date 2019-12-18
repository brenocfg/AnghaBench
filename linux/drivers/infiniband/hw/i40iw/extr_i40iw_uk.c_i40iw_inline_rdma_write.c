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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct i40iw_qp_uk {int swqe_polarity; scalar_t__ push_wqe; scalar_t__ push_db; } ;
struct TYPE_4__ {int tag_off; int stag; } ;
struct i40iw_inline_rdma_write {int len; scalar_t__ data; TYPE_2__ rem_addr; } ;
struct TYPE_3__ {struct i40iw_inline_rdma_write inline_rdma_write; } ;
struct i40iw_post_sq_info {int read_fence; int local_fence; int signaled; int /*<<< orphan*/  wr_id; TYPE_1__ op; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_FRAG_TO ; 
 int /*<<< orphan*/  I40IWQPSQ_INLINEDATAFLAG ; 
 int /*<<< orphan*/  I40IWQPSQ_INLINEDATALEN ; 
 int /*<<< orphan*/  I40IWQPSQ_LOCALFENCE ; 
 int /*<<< orphan*/  I40IWQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IWQPSQ_PUSHWQE ; 
 int /*<<< orphan*/  I40IWQPSQ_READFENCE ; 
 int /*<<< orphan*/  I40IWQPSQ_REMSTAG ; 
 int /*<<< orphan*/  I40IWQPSQ_SIGCOMPL ; 
 int /*<<< orphan*/  I40IWQPSQ_VALID ; 
 int I40IWQP_OP_RDMA_WRITE ; 
 int I40IW_ERR_INVALID_INLINE_DATA_SIZE ; 
 int I40IW_ERR_QP_TOOMANY_WRS_POSTED ; 
 int I40IW_MAX_INLINE_DATA_SIZE ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int i40iw_inline_data_size_to_wqesize (int,int*) ; 
 int* i40iw_qp_get_next_send_wqe (struct i40iw_qp_uk*,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_qp_post_wr (struct i40iw_qp_uk*) ; 
 int /*<<< orphan*/  i40iw_qp_ring_push_db (struct i40iw_qp_uk*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static enum i40iw_status_code i40iw_inline_rdma_write(struct i40iw_qp_uk *qp,
						      struct i40iw_post_sq_info *info,
						      bool post_sq)
{
	u64 *wqe;
	u8 *dest, *src;
	struct i40iw_inline_rdma_write *op_info;
	u64 *push;
	u64 header = 0;
	u32 wqe_idx;
	enum i40iw_status_code ret_code;
	bool read_fence = false;
	u8 wqe_size;

	op_info = &info->op.inline_rdma_write;
	if (op_info->len > I40IW_MAX_INLINE_DATA_SIZE)
		return I40IW_ERR_INVALID_INLINE_DATA_SIZE;

	ret_code = i40iw_inline_data_size_to_wqesize(op_info->len, &wqe_size);
	if (ret_code)
		return ret_code;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, wqe_size, op_info->len, info->wr_id);
	if (!wqe)
		return I40IW_ERR_QP_TOOMANY_WRS_POSTED;

	read_fence |= info->read_fence;
	set_64bit_val(wqe, 16,
		      LS_64(op_info->rem_addr.tag_off, I40IWQPSQ_FRAG_TO));

	header = LS_64(op_info->rem_addr.stag, I40IWQPSQ_REMSTAG) |
		 LS_64(I40IWQP_OP_RDMA_WRITE, I40IWQPSQ_OPCODE) |
		 LS_64(op_info->len, I40IWQPSQ_INLINEDATALEN) |
		 LS_64(1, I40IWQPSQ_INLINEDATAFLAG) |
		 LS_64((qp->push_db ? 1 : 0), I40IWQPSQ_PUSHWQE) |
		 LS_64(read_fence, I40IWQPSQ_READFENCE) |
		 LS_64(info->local_fence, I40IWQPSQ_LOCALFENCE) |
		 LS_64(info->signaled, I40IWQPSQ_SIGCOMPL) |
		 LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	dest = (u8 *)wqe;
	src = (u8 *)(op_info->data);

	if (op_info->len <= 16) {
		memcpy(dest, src, op_info->len);
	} else {
		memcpy(dest, src, 16);
		src += 16;
		dest = (u8 *)wqe + 32;
		memcpy(dest, src, op_info->len - 16);
	}

	wmb(); /* make sure WQE is populated before valid bit is set */

	set_64bit_val(wqe, 24, header);

	if (qp->push_db) {
		push = (u64 *)((uintptr_t)qp->push_wqe + (wqe_idx & 0x3) * 0x20);
		memcpy(push, wqe, (op_info->len > 16) ? op_info->len + 16 : 32);
		i40iw_qp_ring_push_db(qp, wqe_idx);
	} else {
		if (post_sq)
			i40iw_qp_post_wr(qp);
	}

	return 0;
}