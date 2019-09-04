#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_13__ {int remote_qpn; int remote_qkey; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  ah; } ;
struct TYPE_19__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_21__ {scalar_t__ opcode; int send_flags; TYPE_4__ ex; int /*<<< orphan*/  num_sge; } ;
struct rvt_swqe {int length; int psn; TYPE_10__ ud_wr; TYPE_6__ wr; int /*<<< orphan*/ * sg_list; } ;
struct TYPE_24__ {scalar_t__ qp_type; int qp_num; int /*<<< orphan*/  device; } ;
struct TYPE_16__ {int total_len; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/  sge; } ;
struct rvt_qp {size_t state; scalar_t__ s_last; scalar_t__ s_cur; int s_size; int s_hdrwords; int s_cur_size; int qkey; int /*<<< orphan*/  s_flags; TYPE_9__ ibqp; int /*<<< orphan*/  s_pkey_index; TYPE_1__ s_sge; struct rvt_swqe* s_wqe; int /*<<< orphan*/  s_srate; TYPE_1__* s_cur_sge; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  port_num; int /*<<< orphan*/  s_head; struct qib_qp_priv* priv; } ;
struct rdma_ah_attr {int dummy; } ;
struct qib_qp_priv {TYPE_5__* s_hdr; int /*<<< orphan*/  s_dma_busy; } ;
struct qib_pportdata {int lmc; int lid; } ;
struct qib_ibport {int* sl_to_vl; TYPE_11__* pmastats; } ;
struct TYPE_22__ {void** deth; int /*<<< orphan*/  imm_data; } ;
struct TYPE_23__ {TYPE_7__ ud; } ;
struct ib_other_headers {TYPE_8__ u; void** bth; } ;
struct TYPE_17__ {struct ib_other_headers oth; int /*<<< orphan*/  grh; } ;
struct TYPE_18__ {struct ib_other_headers oth; TYPE_2__ l; } ;
struct TYPE_20__ {void** lrh; TYPE_3__ u; } ;
struct TYPE_15__ {struct rdma_ah_attr attr; } ;
struct TYPE_14__ {int /*<<< orphan*/  n_unicast_xmit; int /*<<< orphan*/  n_multicast_xmit; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_BTH_SOLICITED ; 
 void* IB_LID_PERMISSIVE ; 
 void* IB_MULTICAST_LID_BASE ; 
 int IB_OPCODE_UD_SEND_ONLY ; 
 int IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 scalar_t__ IB_WR_SEND_WITH_IMM ; 
 int QIB_DEFAULT_P_KEY ; 
 int QIB_LRH_BTH ; 
 int QIB_LRH_GRH ; 
 int QIB_MULTICAST_QPN ; 
 int QIB_PSN_MASK ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int RVT_FLUSH_SEND ; 
 int RVT_PROCESS_NEXT_SEND_OK ; 
 int /*<<< orphan*/  RVT_S_BUSY ; 
 int /*<<< orphan*/  RVT_S_WAIT_DMA ; 
 int SIZE_OF_CRC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int be16_to_cpu (void*) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int* ib_rvt_state_ops ; 
 TYPE_12__* ibah_to_rvtah (int /*<<< orphan*/ ) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int qib_get_pkey (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 scalar_t__ qib_make_grh (struct qib_ibport*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qib_send_complete (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_ud_loopback (struct rvt_qp*,struct rvt_swqe*) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 size_t rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_static_rate (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int qib_make_ud_req(struct rvt_qp *qp, unsigned long *flags)
{
	struct qib_qp_priv *priv = qp->priv;
	struct ib_other_headers *ohdr;
	struct rdma_ah_attr *ah_attr;
	struct qib_pportdata *ppd;
	struct qib_ibport *ibp;
	struct rvt_swqe *wqe;
	u32 nwords;
	u32 extra_bytes;
	u32 bth0;
	u16 lrh0;
	u16 lid;
	int ret = 0;
	int next_cur;

	if (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_NEXT_SEND_OK)) {
		if (!(ib_rvt_state_ops[qp->state] & RVT_FLUSH_SEND))
			goto bail;
		/* We are in the error state, flush the work request. */
		if (qp->s_last == READ_ONCE(qp->s_head))
			goto bail;
		/* If DMAs are in progress, we can't flush immediately. */
		if (atomic_read(&priv->s_dma_busy)) {
			qp->s_flags |= RVT_S_WAIT_DMA;
			goto bail;
		}
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		qib_send_complete(qp, wqe, IB_WC_WR_FLUSH_ERR);
		goto done;
	}

	/* see post_one_send() */
	if (qp->s_cur == READ_ONCE(qp->s_head))
		goto bail;

	wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
	next_cur = qp->s_cur + 1;
	if (next_cur >= qp->s_size)
		next_cur = 0;

	/* Construct the header. */
	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	ah_attr = &ibah_to_rvtah(wqe->ud_wr.ah)->attr;
	if (rdma_ah_get_dlid(ah_attr) >= be16_to_cpu(IB_MULTICAST_LID_BASE)) {
		if (rdma_ah_get_dlid(ah_attr) !=
				be16_to_cpu(IB_LID_PERMISSIVE))
			this_cpu_inc(ibp->pmastats->n_multicast_xmit);
		else
			this_cpu_inc(ibp->pmastats->n_unicast_xmit);
	} else {
		this_cpu_inc(ibp->pmastats->n_unicast_xmit);
		lid = rdma_ah_get_dlid(ah_attr) & ~((1 << ppd->lmc) - 1);
		if (unlikely(lid == ppd->lid)) {
			unsigned long tflags = *flags;
			/*
			 * If DMAs are in progress, we can't generate
			 * a completion for the loopback packet since
			 * it would be out of order.
			 * XXX Instead of waiting, we could queue a
			 * zero length descriptor so we get a callback.
			 */
			if (atomic_read(&priv->s_dma_busy)) {
				qp->s_flags |= RVT_S_WAIT_DMA;
				goto bail;
			}
			qp->s_cur = next_cur;
			spin_unlock_irqrestore(&qp->s_lock, tflags);
			qib_ud_loopback(qp, wqe);
			spin_lock_irqsave(&qp->s_lock, tflags);
			*flags = tflags;
			qib_send_complete(qp, wqe, IB_WC_SUCCESS);
			goto done;
		}
	}

	qp->s_cur = next_cur;
	extra_bytes = -wqe->length & 3;
	nwords = (wqe->length + extra_bytes) >> 2;

	/* header size in 32-bit words LRH+BTH+DETH = (8+12+8)/4. */
	qp->s_hdrwords = 7;
	qp->s_cur_size = wqe->length;
	qp->s_cur_sge = &qp->s_sge;
	qp->s_srate = rdma_ah_get_static_rate(ah_attr);
	qp->s_wqe = wqe;
	qp->s_sge.sge = wqe->sg_list[0];
	qp->s_sge.sg_list = wqe->sg_list + 1;
	qp->s_sge.num_sge = wqe->wr.num_sge;
	qp->s_sge.total_len = wqe->length;

	if (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) {
		/* Header size in 32-bit words. */
		qp->s_hdrwords += qib_make_grh(ibp, &priv->s_hdr->u.l.grh,
					       rdma_ah_read_grh(ah_attr),
					       qp->s_hdrwords, nwords);
		lrh0 = QIB_LRH_GRH;
		ohdr = &priv->s_hdr->u.l.oth;
		/*
		 * Don't worry about sending to locally attached multicast
		 * QPs.  It is unspecified by the spec. what happens.
		 */
	} else {
		/* Header size in 32-bit words. */
		lrh0 = QIB_LRH_BTH;
		ohdr = &priv->s_hdr->u.oth;
	}
	if (wqe->wr.opcode == IB_WR_SEND_WITH_IMM) {
		qp->s_hdrwords++;
		ohdr->u.ud.imm_data = wqe->wr.ex.imm_data;
		bth0 = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE << 24;
	} else
		bth0 = IB_OPCODE_UD_SEND_ONLY << 24;
	lrh0 |= rdma_ah_get_sl(ah_attr) << 4;
	if (qp->ibqp.qp_type == IB_QPT_SMI)
		lrh0 |= 0xF000; /* Set VL (see ch. 13.5.3.1) */
	else
		lrh0 |= ibp->sl_to_vl[rdma_ah_get_sl(ah_attr)] << 12;
	priv->s_hdr->lrh[0] = cpu_to_be16(lrh0);
	priv->s_hdr->lrh[1] =
			cpu_to_be16(rdma_ah_get_dlid(ah_attr));  /* DEST LID */
	priv->s_hdr->lrh[2] =
			cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	lid = ppd->lid;
	if (lid) {
		lid |= rdma_ah_get_path_bits(ah_attr) &
			((1 << ppd->lmc) - 1);
		priv->s_hdr->lrh[3] = cpu_to_be16(lid);
	} else
		priv->s_hdr->lrh[3] = IB_LID_PERMISSIVE;
	if (wqe->wr.send_flags & IB_SEND_SOLICITED)
		bth0 |= IB_BTH_SOLICITED;
	bth0 |= extra_bytes << 20;
	bth0 |= qp->ibqp.qp_type == IB_QPT_SMI ? QIB_DEFAULT_P_KEY :
		qib_get_pkey(ibp, qp->ibqp.qp_type == IB_QPT_GSI ?
			     wqe->ud_wr.pkey_index : qp->s_pkey_index);
	ohdr->bth[0] = cpu_to_be32(bth0);
	/*
	 * Use the multicast QP if the destination LID is a multicast LID.
	 */
	ohdr->bth[1] = rdma_ah_get_dlid(ah_attr) >=
			be16_to_cpu(IB_MULTICAST_LID_BASE) &&
		rdma_ah_get_dlid(ah_attr) != be16_to_cpu(IB_LID_PERMISSIVE) ?
		cpu_to_be32(QIB_MULTICAST_QPN) :
		cpu_to_be32(wqe->ud_wr.remote_qpn);
	ohdr->bth[2] = cpu_to_be32(wqe->psn & QIB_PSN_MASK);
	/*
	 * Qkeys with the high order bit set mean use the
	 * qkey from the QP context instead of the WR (see 10.2.5).
	 */
	ohdr->u.ud.deth[0] = cpu_to_be32((int)wqe->ud_wr.remote_qkey < 0 ?
					 qp->qkey : wqe->ud_wr.remote_qkey);
	ohdr->u.ud.deth[1] = cpu_to_be32(qp->ibqp.qp_num);

done:
	return 1;
bail:
	qp->s_flags &= ~RVT_S_BUSY;
	return ret;
}