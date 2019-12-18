#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_24__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_send_wr {int send_flags; int opcode; struct ib_send_wr* next; void* wr_id; TYPE_10__ ex; TYPE_17__* sg_list; int /*<<< orphan*/  num_sge; } ;
struct ib_qp {int dummy; } ;
struct i40iw_sge {int dummy; } ;
struct i40iw_sc_dev {TYPE_15__* iw_priv_qp_ops; } ;
struct TYPE_30__ {int (* iw_inline_send ) (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int /*<<< orphan*/ ,int) ;int (* iw_send ) (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int /*<<< orphan*/ ,int) ;int (* iw_inline_rdma_write ) (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int) ;int (* iw_rdma_write ) (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int) ;int (* iw_rdma_read ) (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int,int) ;int (* iw_stag_local_invalidate ) (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int) ;int /*<<< orphan*/  (* iw_qp_post_wr ) (struct i40iw_qp_uk*) ;} ;
struct i40iw_qp_uk {TYPE_16__ ops; } ;
struct TYPE_36__ {struct i40iw_qp_uk qp_uk; } ;
struct i40iw_qp {int /*<<< orphan*/  lock; TYPE_21__ sc_qp; TYPE_12__* iwdev; scalar_t__ sig_all; scalar_t__ flush_issued; } ;
struct TYPE_46__ {int /*<<< orphan*/  target_stag; } ;
struct TYPE_44__ {int /*<<< orphan*/  len; int /*<<< orphan*/  stag; scalar_t__ tag_off; } ;
struct TYPE_43__ {int /*<<< orphan*/  stag; int /*<<< orphan*/  tag_off; } ;
struct TYPE_45__ {TYPE_7__ lo_addr; TYPE_6__ rem_addr; } ;
struct TYPE_41__ {int /*<<< orphan*/  stag; int /*<<< orphan*/  tag_off; } ;
struct TYPE_42__ {TYPE_4__ rem_addr; int /*<<< orphan*/  num_lo_sges; void* lo_sg_list; } ;
struct TYPE_39__ {int /*<<< orphan*/  stag; int /*<<< orphan*/  tag_off; } ;
struct TYPE_40__ {TYPE_2__ rem_addr; int /*<<< orphan*/  len; void* data; } ;
struct TYPE_34__ {struct i40iw_sge* sg_list; int /*<<< orphan*/  num_sges; } ;
struct TYPE_33__ {int /*<<< orphan*/  len; void* data; } ;
struct TYPE_32__ {TYPE_9__ inv_local_stag; TYPE_8__ rdma_read; TYPE_5__ rdma_write; TYPE_3__ inline_rdma_write; TYPE_1__ send; TYPE_19__ inline_send; } ;
struct i40iw_post_sq_info {int signaled; int read_fence; int stag_key; int stag_idx; int local_fence; int chunk_size; int /*<<< orphan*/  first_pm_pbl_index; void* reg_addr_pa; int /*<<< orphan*/  total_len; void* va; int /*<<< orphan*/  addr_type; void* wr_id; int /*<<< orphan*/  page_size; int /*<<< orphan*/  access_rights; TYPE_18__ op; int /*<<< orphan*/  op_type; } ;
struct TYPE_28__ {int /*<<< orphan*/  idx; scalar_t__ addr; } ;
struct i40iw_pble_alloc {TYPE_14__ level1; } ;
struct TYPE_27__ {int /*<<< orphan*/  length; int /*<<< orphan*/  iova; } ;
struct TYPE_25__ {struct i40iw_pble_alloc pble_alloc; } ;
struct i40iw_mr {int /*<<< orphan*/  npages; TYPE_13__ ibmr; TYPE_11__ iwpbl; } ;
struct i40iw_fast_reg_stag_info {int signaled; int read_fence; int stag_key; int stag_idx; int local_fence; int chunk_size; int /*<<< orphan*/  first_pm_pbl_index; void* reg_addr_pa; int /*<<< orphan*/  total_len; void* va; int /*<<< orphan*/  addr_type; void* wr_id; int /*<<< orphan*/  page_size; int /*<<< orphan*/  access_rights; TYPE_18__ op; int /*<<< orphan*/  op_type; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_38__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_37__ {int access; int key; TYPE_20__* mr; } ;
struct TYPE_35__ {int /*<<< orphan*/  page_size; } ;
struct TYPE_31__ {int /*<<< orphan*/  length; int /*<<< orphan*/  lkey; scalar_t__ addr; } ;
struct TYPE_29__ {int (* iw_mr_fast_register ) (TYPE_21__*,struct i40iw_post_sq_info*,int) ;} ;
struct TYPE_26__ {struct i40iw_sc_dev sc_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_LOCALREAD ; 
 int /*<<< orphan*/  I40IW_ADDR_TYPE_VA_BASED ; 
 int I40IW_ERR_QP_TOOMANY_WRS_POSTED ; 
 int /*<<< orphan*/  I40IW_MAX_SGE_RD ; 
 int /*<<< orphan*/  I40IW_MIN_PAGES_PER_FMR ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_INV_STAG ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_RDMA_READ ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_RDMA_WRITE ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_SEND ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_SEND_INV ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_SEND_SOL ; 
 int /*<<< orphan*/  I40IW_OP_TYPE_SEND_SOL_INV ; 
 int IB_SEND_FENCE ; 
 int IB_SEND_INLINE ; 
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_LOCAL_INV 134 
#define  IB_WR_RDMA_READ 133 
#define  IB_WR_RDMA_READ_WITH_INV 132 
#define  IB_WR_RDMA_WRITE 131 
#define  IB_WR_REG_MR 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_INV 128 
 int /*<<< orphan*/  i40iw_get_user_access (int) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int const) ; 
 int /*<<< orphan*/  memset (struct i40iw_post_sq_info*,int /*<<< orphan*/ ,int) ; 
 TYPE_23__* rdma_wr (struct ib_send_wr const*) ; 
 TYPE_22__* reg_wr (struct ib_send_wr const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int) ; 
 int stub4 (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int) ; 
 int stub5 (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int,int) ; 
 int stub6 (struct i40iw_qp_uk*,struct i40iw_post_sq_info*,int) ; 
 int stub7 (TYPE_21__*,struct i40iw_post_sq_info*,int) ; 
 int /*<<< orphan*/  stub8 (struct i40iw_qp_uk*) ; 
 struct i40iw_mr* to_iwmr (TYPE_20__*) ; 

__attribute__((used)) static int i40iw_post_send(struct ib_qp *ibqp,
			   const struct ib_send_wr *ib_wr,
			   const struct ib_send_wr **bad_wr)
{
	struct i40iw_qp *iwqp;
	struct i40iw_qp_uk *ukqp;
	struct i40iw_post_sq_info info;
	enum i40iw_status_code ret;
	int err = 0;
	unsigned long flags;
	bool inv_stag;

	iwqp = (struct i40iw_qp *)ibqp;
	ukqp = &iwqp->sc_qp.qp_uk;

	spin_lock_irqsave(&iwqp->lock, flags);

	if (iwqp->flush_issued) {
		err = -EINVAL;
		goto out;
	}

	while (ib_wr) {
		inv_stag = false;
		memset(&info, 0, sizeof(info));
		info.wr_id = (u64)(ib_wr->wr_id);
		if ((ib_wr->send_flags & IB_SEND_SIGNALED) || iwqp->sig_all)
			info.signaled = true;
		if (ib_wr->send_flags & IB_SEND_FENCE)
			info.read_fence = true;

		switch (ib_wr->opcode) {
		case IB_WR_SEND:
			/* fall-through */
		case IB_WR_SEND_WITH_INV:
			if (ib_wr->opcode == IB_WR_SEND) {
				if (ib_wr->send_flags & IB_SEND_SOLICITED)
					info.op_type = I40IW_OP_TYPE_SEND_SOL;
				else
					info.op_type = I40IW_OP_TYPE_SEND;
			} else {
				if (ib_wr->send_flags & IB_SEND_SOLICITED)
					info.op_type = I40IW_OP_TYPE_SEND_SOL_INV;
				else
					info.op_type = I40IW_OP_TYPE_SEND_INV;
			}

			if (ib_wr->send_flags & IB_SEND_INLINE) {
				info.op.inline_send.data = (void *)(unsigned long)ib_wr->sg_list[0].addr;
				info.op.inline_send.len = ib_wr->sg_list[0].length;
				ret = ukqp->ops.iw_inline_send(ukqp, &info, ib_wr->ex.invalidate_rkey, false);
			} else {
				info.op.send.num_sges = ib_wr->num_sge;
				info.op.send.sg_list = (struct i40iw_sge *)ib_wr->sg_list;
				ret = ukqp->ops.iw_send(ukqp, &info, ib_wr->ex.invalidate_rkey, false);
			}

			if (ret) {
				if (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
					err = -ENOMEM;
				else
					err = -EINVAL;
			}
			break;
		case IB_WR_RDMA_WRITE:
			info.op_type = I40IW_OP_TYPE_RDMA_WRITE;

			if (ib_wr->send_flags & IB_SEND_INLINE) {
				info.op.inline_rdma_write.data = (void *)(unsigned long)ib_wr->sg_list[0].addr;
				info.op.inline_rdma_write.len = ib_wr->sg_list[0].length;
				info.op.inline_rdma_write.rem_addr.tag_off = rdma_wr(ib_wr)->remote_addr;
				info.op.inline_rdma_write.rem_addr.stag = rdma_wr(ib_wr)->rkey;
				ret = ukqp->ops.iw_inline_rdma_write(ukqp, &info, false);
			} else {
				info.op.rdma_write.lo_sg_list = (void *)ib_wr->sg_list;
				info.op.rdma_write.num_lo_sges = ib_wr->num_sge;
				info.op.rdma_write.rem_addr.tag_off = rdma_wr(ib_wr)->remote_addr;
				info.op.rdma_write.rem_addr.stag = rdma_wr(ib_wr)->rkey;
				ret = ukqp->ops.iw_rdma_write(ukqp, &info, false);
			}

			if (ret) {
				if (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
					err = -ENOMEM;
				else
					err = -EINVAL;
			}
			break;
		case IB_WR_RDMA_READ_WITH_INV:
			inv_stag = true;
			/* fall-through*/
		case IB_WR_RDMA_READ:
			if (ib_wr->num_sge > I40IW_MAX_SGE_RD) {
				err = -EINVAL;
				break;
			}
			info.op_type = I40IW_OP_TYPE_RDMA_READ;
			info.op.rdma_read.rem_addr.tag_off = rdma_wr(ib_wr)->remote_addr;
			info.op.rdma_read.rem_addr.stag = rdma_wr(ib_wr)->rkey;
			info.op.rdma_read.lo_addr.tag_off = ib_wr->sg_list->addr;
			info.op.rdma_read.lo_addr.stag = ib_wr->sg_list->lkey;
			info.op.rdma_read.lo_addr.len = ib_wr->sg_list->length;
			ret = ukqp->ops.iw_rdma_read(ukqp, &info, inv_stag, false);
			if (ret) {
				if (ret == I40IW_ERR_QP_TOOMANY_WRS_POSTED)
					err = -ENOMEM;
				else
					err = -EINVAL;
			}
			break;
		case IB_WR_LOCAL_INV:
			info.op_type = I40IW_OP_TYPE_INV_STAG;
			info.op.inv_local_stag.target_stag = ib_wr->ex.invalidate_rkey;
			ret = ukqp->ops.iw_stag_local_invalidate(ukqp, &info, true);
			if (ret)
				err = -ENOMEM;
			break;
		case IB_WR_REG_MR:
		{
			struct i40iw_mr *iwmr = to_iwmr(reg_wr(ib_wr)->mr);
			int flags = reg_wr(ib_wr)->access;
			struct i40iw_pble_alloc *palloc = &iwmr->iwpbl.pble_alloc;
			struct i40iw_sc_dev *dev = &iwqp->iwdev->sc_dev;
			struct i40iw_fast_reg_stag_info info;

			memset(&info, 0, sizeof(info));
			info.access_rights = I40IW_ACCESS_FLAGS_LOCALREAD;
			info.access_rights |= i40iw_get_user_access(flags);
			info.stag_key = reg_wr(ib_wr)->key & 0xff;
			info.stag_idx = reg_wr(ib_wr)->key >> 8;
			info.page_size = reg_wr(ib_wr)->mr->page_size;
			info.wr_id = ib_wr->wr_id;

			info.addr_type = I40IW_ADDR_TYPE_VA_BASED;
			info.va = (void *)(uintptr_t)iwmr->ibmr.iova;
			info.total_len = iwmr->ibmr.length;
			info.reg_addr_pa = *(u64 *)palloc->level1.addr;
			info.first_pm_pbl_index = palloc->level1.idx;
			info.local_fence = ib_wr->send_flags & IB_SEND_FENCE;
			info.signaled = ib_wr->send_flags & IB_SEND_SIGNALED;

			if (iwmr->npages > I40IW_MIN_PAGES_PER_FMR)
				info.chunk_size = 1;

			ret = dev->iw_priv_qp_ops->iw_mr_fast_register(&iwqp->sc_qp, &info, true);
			if (ret)
				err = -ENOMEM;
			break;
		}
		default:
			err = -EINVAL;
			i40iw_pr_err(" upost_send bad opcode = 0x%x\n",
				     ib_wr->opcode);
			break;
		}

		if (err)
			break;
		ib_wr = ib_wr->next;
	}

out:
	if (err)
		*bad_wr = ib_wr;
	else
		ukqp->ops.iw_qp_post_wr(ukqp);
	spin_unlock_irqrestore(&iwqp->lock, flags);

	return err;
}