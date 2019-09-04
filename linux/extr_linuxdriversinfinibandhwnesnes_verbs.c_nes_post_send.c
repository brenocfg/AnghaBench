#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct TYPE_13__ {int sq_size; int sq_head; int sq_tail; int qp_id; struct nes_hw_qp_wqe* sq_vbase; } ;
struct nes_qp {scalar_t__ ibqp_state; int /*<<< orphan*/  lock; TYPE_5__ hwqp; scalar_t__ sig_all; scalar_t__ term_flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  length; scalar_t__ iova; } ;
struct nes_mr {int npages; scalar_t__ paddr; TYPE_4__ ibmr; } ;
struct nes_hw_qp_wqe {int /*<<< orphan*/ * wqe_words; } ;
struct nes_device {scalar_t__ regs; TYPE_1__* nesadapter; } ;
struct TYPE_11__ {int invalidate_rkey; } ;
struct ib_send_wr {int opcode; int send_flags; int num_sge; struct ib_send_wr* next; TYPE_3__ ex; TYPE_2__* sg_list; scalar_t__ wr_id; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_16__ {int rkey; scalar_t__ remote_addr; } ;
struct TYPE_15__ {int access; int key; TYPE_6__* mr; } ;
struct TYPE_14__ {int /*<<< orphan*/  page_size; } ;
struct TYPE_10__ {int length; int lkey; scalar_t__ addr; } ;
struct TYPE_9__ {int max_sge; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IB_QPS_RTS ; 
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
 int NES_4K_PBL_CHUNK_SIZE ; 
 int /*<<< orphan*/  NES_DBG_IW_TX ; 
 int NES_DRV_OPT_NO_INLINE_DATA ; 
 size_t NES_IWARP_SQ_FMR_WQE_LENGTH_HIGH_IDX ; 
 size_t NES_IWARP_SQ_FMR_WQE_LENGTH_LOW_IDX ; 
 size_t NES_IWARP_SQ_FMR_WQE_MR_STAG_IDX ; 
 int NES_IWARP_SQ_FMR_WQE_PAGE_SIZE_2M ; 
 int NES_IWARP_SQ_FMR_WQE_PAGE_SIZE_4K ; 
 int /*<<< orphan*/  NES_IWARP_SQ_FMR_WQE_PBL_ADDR_LOW_IDX ; 
 size_t NES_IWARP_SQ_FMR_WQE_PBL_LENGTH_IDX ; 
 int NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_LOCAL_READ ; 
 int NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_LOCAL_WRITE ; 
 int NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_REMOTE_READ ; 
 int NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_REMOTE_WRITE ; 
 int NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_WINDOW_BIND ; 
 int /*<<< orphan*/  NES_IWARP_SQ_FMR_WQE_VA_FBO_LOW_IDX ; 
 size_t NES_IWARP_SQ_LOCINV_WQE_INV_STAG_IDX ; 
 int NES_IWARP_SQ_OP_FAST_REG ; 
 int NES_IWARP_SQ_OP_LOCINV ; 
 int NES_IWARP_SQ_OP_RDMAR ; 
 int NES_IWARP_SQ_OP_RDMAR_LOCINV ; 
 int NES_IWARP_SQ_OP_RDMAW ; 
 int NES_IWARP_SQ_OP_SEND ; 
 int NES_IWARP_SQ_OP_SENDINV ; 
 int NES_IWARP_SQ_OP_SENDSE ; 
 int NES_IWARP_SQ_OP_SENDSEINV ; 
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_COMP_SCRATCH_LOW_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_FRAG0_LOW_IDX ; 
 int NES_IWARP_SQ_WQE_IMM_DATA ; 
 size_t NES_IWARP_SQ_WQE_IMM_DATA_START_IDX ; 
 size_t NES_IWARP_SQ_WQE_INV_STAG_LOW_IDX ; 
 int NES_IWARP_SQ_WQE_LOCAL_FENCE ; 
 size_t NES_IWARP_SQ_WQE_MISC_IDX ; 
 size_t NES_IWARP_SQ_WQE_RDMA_LENGTH_IDX ; 
 size_t NES_IWARP_SQ_WQE_RDMA_STAG_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_RDMA_TO_LOW_IDX ; 
 int NES_IWARP_SQ_WQE_SIGNALED_COMPL ; 
 size_t NES_IWARP_SQ_WQE_STAG0_IDX ; 
 size_t NES_IWARP_SQ_WQE_TOTAL_PAYLOAD_IDX ; 
 scalar_t__ NES_WQE_ALLOC ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  fill_wqe_sg_send (struct nes_hw_qp_wqe*,struct ib_send_wr const*,int) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int nes_drv_opt ; 
 int /*<<< orphan*/  nes_fill_init_qp_wqe (struct nes_hw_qp_wqe*,struct nes_qp*,int) ; 
 int /*<<< orphan*/  nes_write32 (scalar_t__,int) ; 
 TYPE_8__* rdma_wr (struct ib_send_wr const*) ; 
 TYPE_7__* reg_wr (struct ib_send_wr const*) ; 
 int /*<<< orphan*/  set_wqe_32bit_value (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  set_wqe_64bit_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct nes_mr* to_nesmr (TYPE_6__*) ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nes_post_send(struct ib_qp *ibqp, const struct ib_send_wr *ib_wr,
			 const struct ib_send_wr **bad_wr)
{
	u64 u64temp;
	unsigned long flags = 0;
	struct nes_vnic *nesvnic = to_nesvnic(ibqp->device);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_qp *nesqp = to_nesqp(ibqp);
	struct nes_hw_qp_wqe *wqe;
	int err = 0;
	u32 qsize = nesqp->hwqp.sq_size;
	u32 head;
	u32 wqe_misc = 0;
	u32 wqe_count = 0;
	u32 counter;

	if (nesqp->ibqp_state > IB_QPS_RTS) {
		err = -EINVAL;
		goto out;
	}

	spin_lock_irqsave(&nesqp->lock, flags);

	head = nesqp->hwqp.sq_head;

	while (ib_wr) {
		/* Check for QP error */
		if (nesqp->term_flags) {
			err = -EINVAL;
			break;
		}

		/* Check for SQ overflow */
		if (((head + (2 * qsize) - nesqp->hwqp.sq_tail) % qsize) == (qsize - 1)) {
			err = -ENOMEM;
			break;
		}

		wqe = &nesqp->hwqp.sq_vbase[head];
		/* nes_debug(NES_DBG_IW_TX, "processing sq wqe for QP%u at %p, head = %u.\n",
				nesqp->hwqp.qp_id, wqe, head); */
		nes_fill_init_qp_wqe(wqe, nesqp, head);
		u64temp = (u64)(ib_wr->wr_id);
		set_wqe_64bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_COMP_SCRATCH_LOW_IDX,
					u64temp);
		switch (ib_wr->opcode) {
		case IB_WR_SEND:
		case IB_WR_SEND_WITH_INV:
			if (IB_WR_SEND == ib_wr->opcode) {
				if (ib_wr->send_flags & IB_SEND_SOLICITED)
					wqe_misc = NES_IWARP_SQ_OP_SENDSE;
				else
					wqe_misc = NES_IWARP_SQ_OP_SEND;
			} else {
				if (ib_wr->send_flags & IB_SEND_SOLICITED)
					wqe_misc = NES_IWARP_SQ_OP_SENDSEINV;
				else
					wqe_misc = NES_IWARP_SQ_OP_SENDINV;

				set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_INV_STAG_LOW_IDX,
						    ib_wr->ex.invalidate_rkey);
			}

			if (ib_wr->num_sge > nesdev->nesadapter->max_sge) {
				err = -EINVAL;
				break;
			}

			if (ib_wr->send_flags & IB_SEND_FENCE)
				wqe_misc |= NES_IWARP_SQ_WQE_LOCAL_FENCE;

			if ((ib_wr->send_flags & IB_SEND_INLINE) &&
			    ((nes_drv_opt & NES_DRV_OPT_NO_INLINE_DATA) == 0) &&
			     (ib_wr->sg_list[0].length <= 64)) {
				memcpy(&wqe->wqe_words[NES_IWARP_SQ_WQE_IMM_DATA_START_IDX],
				       (void *)(unsigned long)ib_wr->sg_list[0].addr, ib_wr->sg_list[0].length);
				set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_TOTAL_PAYLOAD_IDX,
						    ib_wr->sg_list[0].length);
				wqe_misc |= NES_IWARP_SQ_WQE_IMM_DATA;
			} else {
				fill_wqe_sg_send(wqe, ib_wr, 1);
			}

			break;
		case IB_WR_RDMA_WRITE:
			wqe_misc = NES_IWARP_SQ_OP_RDMAW;
			if (ib_wr->num_sge > nesdev->nesadapter->max_sge) {
				nes_debug(NES_DBG_IW_TX, "Exceeded max sge, ib_wr=%u, max=%u\n",
					  ib_wr->num_sge, nesdev->nesadapter->max_sge);
				err = -EINVAL;
				break;
			}

			if (ib_wr->send_flags & IB_SEND_FENCE)
				wqe_misc |= NES_IWARP_SQ_WQE_LOCAL_FENCE;

			set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_RDMA_STAG_IDX,
					    rdma_wr(ib_wr)->rkey);
			set_wqe_64bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_RDMA_TO_LOW_IDX,
					    rdma_wr(ib_wr)->remote_addr);

			if ((ib_wr->send_flags & IB_SEND_INLINE) &&
			    ((nes_drv_opt & NES_DRV_OPT_NO_INLINE_DATA) == 0) &&
			     (ib_wr->sg_list[0].length <= 64)) {
				memcpy(&wqe->wqe_words[NES_IWARP_SQ_WQE_IMM_DATA_START_IDX],
				       (void *)(unsigned long)ib_wr->sg_list[0].addr, ib_wr->sg_list[0].length);
				set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_TOTAL_PAYLOAD_IDX,
						    ib_wr->sg_list[0].length);
				wqe_misc |= NES_IWARP_SQ_WQE_IMM_DATA;
			} else {
				fill_wqe_sg_send(wqe, ib_wr, 1);
			}

			wqe->wqe_words[NES_IWARP_SQ_WQE_RDMA_LENGTH_IDX] =
				wqe->wqe_words[NES_IWARP_SQ_WQE_TOTAL_PAYLOAD_IDX];
			break;
		case IB_WR_RDMA_READ:
		case IB_WR_RDMA_READ_WITH_INV:
			/* iWARP only supports 1 sge for RDMA reads */
			if (ib_wr->num_sge > 1) {
				nes_debug(NES_DBG_IW_TX, "Exceeded max sge, ib_wr=%u, max=1\n",
					  ib_wr->num_sge);
				err = -EINVAL;
				break;
			}
			if (ib_wr->opcode == IB_WR_RDMA_READ) {
				wqe_misc = NES_IWARP_SQ_OP_RDMAR;
			} else {
				wqe_misc = NES_IWARP_SQ_OP_RDMAR_LOCINV;
				set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_INV_STAG_LOW_IDX,
						    ib_wr->ex.invalidate_rkey);
			}

			set_wqe_64bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_RDMA_TO_LOW_IDX,
					    rdma_wr(ib_wr)->remote_addr);
			set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_RDMA_STAG_IDX,
					    rdma_wr(ib_wr)->rkey);
			set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_RDMA_LENGTH_IDX,
					    ib_wr->sg_list->length);
			set_wqe_64bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_FRAG0_LOW_IDX,
					    ib_wr->sg_list->addr);
			set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_STAG0_IDX,
					    ib_wr->sg_list->lkey);
			break;
		case IB_WR_LOCAL_INV:
			wqe_misc = NES_IWARP_SQ_OP_LOCINV;
			set_wqe_32bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_LOCINV_WQE_INV_STAG_IDX,
					    ib_wr->ex.invalidate_rkey);
			break;
		case IB_WR_REG_MR:
		{
			struct nes_mr *mr = to_nesmr(reg_wr(ib_wr)->mr);
			int page_shift = ilog2(reg_wr(ib_wr)->mr->page_size);
			int flags = reg_wr(ib_wr)->access;

			if (mr->npages > (NES_4K_PBL_CHUNK_SIZE / sizeof(u64))) {
				nes_debug(NES_DBG_IW_TX, "SQ_FMR: bad page_list_len\n");
				err = -EINVAL;
				break;
			}
			wqe_misc = NES_IWARP_SQ_OP_FAST_REG;
			set_wqe_64bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_FMR_WQE_VA_FBO_LOW_IDX,
					    mr->ibmr.iova);
			set_wqe_32bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_FMR_WQE_LENGTH_LOW_IDX,
					    lower_32_bits(mr->ibmr.length));
			set_wqe_32bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_FMR_WQE_LENGTH_HIGH_IDX, 0);
			set_wqe_32bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_FMR_WQE_MR_STAG_IDX,
					    reg_wr(ib_wr)->key);

			if (page_shift == 12) {
				wqe_misc |= NES_IWARP_SQ_FMR_WQE_PAGE_SIZE_4K;
			} else if (page_shift == 21) {
				wqe_misc |= NES_IWARP_SQ_FMR_WQE_PAGE_SIZE_2M;
			} else {
				nes_debug(NES_DBG_IW_TX, "Invalid page shift,"
					  " ib_wr=%u, max=1\n", ib_wr->num_sge);
				err = -EINVAL;
				break;
			}

			/* Set access_flags */
			wqe_misc |= NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_LOCAL_READ;
			if (flags & IB_ACCESS_LOCAL_WRITE)
				wqe_misc |= NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_LOCAL_WRITE;

			if (flags & IB_ACCESS_REMOTE_WRITE)
				wqe_misc |= NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_REMOTE_WRITE;

			if (flags & IB_ACCESS_REMOTE_READ)
				wqe_misc |= NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_REMOTE_READ;

			if (flags & IB_ACCESS_MW_BIND)
				wqe_misc |= NES_IWARP_SQ_FMR_WQE_RIGHTS_ENABLE_WINDOW_BIND;

			/* Fill in PBL info: */
			set_wqe_64bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_FMR_WQE_PBL_ADDR_LOW_IDX,
					    mr->paddr);

			set_wqe_32bit_value(wqe->wqe_words,
					    NES_IWARP_SQ_FMR_WQE_PBL_LENGTH_IDX,
					    mr->npages * 8);

			nes_debug(NES_DBG_IW_TX, "SQ_REG_MR: iova_start: %llx, "
				  "length: %lld, rkey: %0x, pgl_paddr: %llx, "
				  "page_list_len: %u, wqe_misc: %x\n",
				  (unsigned long long) mr->ibmr.iova,
				  mr->ibmr.length,
				  reg_wr(ib_wr)->key,
				  (unsigned long long) mr->paddr,
				  mr->npages,
				  wqe_misc);
			break;
		}
		default:
			/* error */
			err = -EINVAL;
			break;
		}

		if (err)
			break;

		if ((ib_wr->send_flags & IB_SEND_SIGNALED) || nesqp->sig_all)
			wqe_misc |= NES_IWARP_SQ_WQE_SIGNALED_COMPL;

		wqe->wqe_words[NES_IWARP_SQ_WQE_MISC_IDX] = cpu_to_le32(wqe_misc);

		ib_wr = ib_wr->next;
		head++;
		wqe_count++;
		if (head >= qsize)
			head = 0;

	}

	nesqp->hwqp.sq_head = head;
	barrier();
	while (wqe_count) {
		counter = min(wqe_count, ((u32)255));
		wqe_count -= counter;
		nes_write32(nesdev->regs + NES_WQE_ALLOC,
				(counter << 24) | 0x00800000 | nesqp->hwqp.qp_id);
	}

	spin_unlock_irqrestore(&nesqp->lock, flags);

out:
	if (err)
		*bad_wr = ib_wr;
	return err;
}