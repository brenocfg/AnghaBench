#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wc ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_15__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_19__ {scalar_t__ opcode; int send_flags; scalar_t__ num_sge; TYPE_2__ ex; } ;
struct TYPE_21__ {scalar_t__ remote_qkey; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  ah; int /*<<< orphan*/  remote_qpn; } ;
struct rvt_swqe {scalar_t__ length; TYPE_6__ wr; TYPE_8__ ud_wr; struct rvt_sge* sg_list; } ;
struct rvt_sge {scalar_t__ length; scalar_t__ sge_length; scalar_t__ n; scalar_t__ m; TYPE_5__* mr; struct ib_grh* vaddr; } ;
struct rvt_sge_state {struct rvt_sge* sg_list; scalar_t__ num_sge; struct rvt_sge sge; } ;
struct TYPE_22__ {scalar_t__ qp_type; int qp_num; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  device; } ;
struct rvt_qp {size_t state; scalar_t__ qkey; int r_flags; scalar_t__ r_len; int /*<<< orphan*/  r_lock; TYPE_9__ ibqp; int /*<<< orphan*/  port_num; int /*<<< orphan*/  r_wr_id; int /*<<< orphan*/  r_aflags; int /*<<< orphan*/  r_sge; int /*<<< orphan*/  s_pkey_index; } ;
struct rvt_dev_info {int dummy; } ;
struct rdma_ah_attr {int dummy; } ;
struct qib_pportdata {int lid; int lmc; struct qib_devdata* dd; } ;
struct TYPE_12__ {int /*<<< orphan*/  n_loop_pkts; int /*<<< orphan*/  n_pkt_drops; int /*<<< orphan*/  n_vl15_dropped; } ;
struct qib_ibport {TYPE_10__ rvp; } ;
struct TYPE_20__ {struct rvt_dev_info rdi; } ;
struct qib_devdata {TYPE_7__ verbs_dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ byte_len; int src_qp; int slid; int dlid_path_bits; int /*<<< orphan*/  port_num; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey_index; TYPE_9__* qp; int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  wc_flags; TYPE_1__ ex; } ;
struct ib_grh {int dummy; } ;
struct ib_global_route {int dummy; } ;
typedef  int /*<<< orphan*/  grh ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_18__ {scalar_t__ mapsz; TYPE_4__** map; scalar_t__ lkey; } ;
struct TYPE_17__ {TYPE_3__* segs; } ;
struct TYPE_16__ {scalar_t__ length; struct ib_grh* vaddr; } ;
struct TYPE_13__ {struct rdma_ah_attr attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IB_AH_GRH ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_QPT_UD ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IB_WC_GRH ; 
 int /*<<< orphan*/  IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WITH_IMM ; 
 scalar_t__ IB_WR_SEND_WITH_IMM ; 
 int RVT_PROCESS_RECV_OK ; 
 int RVT_R_REUSE_SGE ; 
 int /*<<< orphan*/  RVT_R_WRID_VALID ; 
 scalar_t__ RVT_SEGSZ ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int* ib_rvt_state_ops ; 
 TYPE_11__* ibah_to_rvtah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibcq_to_rvtcq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_bad_pkey (struct qib_ibport*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_copy_sge (int /*<<< orphan*/ *,struct ib_grh*,scalar_t__,int) ; 
 int qib_get_pkey (struct qib_ibport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_make_grh (struct qib_ibport*,struct ib_grh*,struct ib_global_route const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_pkey_ok (int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rvt_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int rvt_get_rwqe (struct rvt_qp*,int) ; 
 struct rvt_qp* rvt_lookup_qpn (struct rvt_dev_info*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_put_ss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_rc_error (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_skip_sge (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qib_ud_loopback(struct rvt_qp *sqp, struct rvt_swqe *swqe)
{
	struct qib_ibport *ibp = to_iport(sqp->ibqp.device, sqp->port_num);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct qib_devdata *dd = ppd->dd;
	struct rvt_dev_info *rdi = &dd->verbs_dev.rdi;
	struct rvt_qp *qp;
	struct rdma_ah_attr *ah_attr;
	unsigned long flags;
	struct rvt_sge_state ssge;
	struct rvt_sge *sge;
	struct ib_wc wc;
	u32 length;
	enum ib_qp_type sqptype, dqptype;

	rcu_read_lock();
	qp = rvt_lookup_qpn(rdi, &ibp->rvp, swqe->ud_wr.remote_qpn);
	if (!qp) {
		ibp->rvp.n_pkt_drops++;
		goto drop;
	}

	sqptype = sqp->ibqp.qp_type == IB_QPT_GSI ?
			IB_QPT_UD : sqp->ibqp.qp_type;
	dqptype = qp->ibqp.qp_type == IB_QPT_GSI ?
			IB_QPT_UD : qp->ibqp.qp_type;

	if (dqptype != sqptype ||
	    !(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) {
		ibp->rvp.n_pkt_drops++;
		goto drop;
	}

	ah_attr = &ibah_to_rvtah(swqe->ud_wr.ah)->attr;
	ppd = ppd_from_ibp(ibp);

	if (qp->ibqp.qp_num > 1) {
		u16 pkey1;
		u16 pkey2;
		u16 lid;

		pkey1 = qib_get_pkey(ibp, sqp->s_pkey_index);
		pkey2 = qib_get_pkey(ibp, qp->s_pkey_index);
		if (unlikely(!qib_pkey_ok(pkey1, pkey2))) {
			lid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
					  ((1 << ppd->lmc) - 1));
			qib_bad_pkey(ibp, pkey1,
				     rdma_ah_get_sl(ah_attr),
				     sqp->ibqp.qp_num, qp->ibqp.qp_num,
				     cpu_to_be16(lid),
				     cpu_to_be16(rdma_ah_get_dlid(ah_attr)));
			goto drop;
		}
	}

	/*
	 * Check that the qkey matches (except for QP0, see 9.6.1.4.1).
	 * Qkeys with the high order bit set mean use the
	 * qkey from the QP context instead of the WR (see 10.2.5).
	 */
	if (qp->ibqp.qp_num) {
		u32 qkey;

		qkey = (int)swqe->ud_wr.remote_qkey < 0 ?
			sqp->qkey : swqe->ud_wr.remote_qkey;
		if (unlikely(qkey != qp->qkey))
			goto drop;
	}

	/*
	 * A GRH is expected to precede the data even if not
	 * present on the wire.
	 */
	length = swqe->length;
	memset(&wc, 0, sizeof(wc));
	wc.byte_len = length + sizeof(struct ib_grh);

	if (swqe->wr.opcode == IB_WR_SEND_WITH_IMM) {
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = swqe->wr.ex.imm_data;
	}

	spin_lock_irqsave(&qp->r_lock, flags);

	/*
	 * Get the next work request entry to find where to put the data.
	 */
	if (qp->r_flags & RVT_R_REUSE_SGE)
		qp->r_flags &= ~RVT_R_REUSE_SGE;
	else {
		int ret;

		ret = rvt_get_rwqe(qp, false);
		if (ret < 0) {
			rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
			goto bail_unlock;
		}
		if (!ret) {
			if (qp->ibqp.qp_num == 0)
				ibp->rvp.n_vl15_dropped++;
			goto bail_unlock;
		}
	}
	/* Silently drop packets which are too big. */
	if (unlikely(wc.byte_len > qp->r_len)) {
		qp->r_flags |= RVT_R_REUSE_SGE;
		ibp->rvp.n_pkt_drops++;
		goto bail_unlock;
	}

	if (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) {
		struct ib_grh grh;
		const struct ib_global_route *grd = rdma_ah_read_grh(ah_attr);

		qib_make_grh(ibp, &grh, grd, 0, 0);
		qib_copy_sge(&qp->r_sge, &grh,
			     sizeof(grh), 1);
		wc.wc_flags |= IB_WC_GRH;
	} else
		rvt_skip_sge(&qp->r_sge, sizeof(struct ib_grh), true);
	ssge.sg_list = swqe->sg_list + 1;
	ssge.sge = *swqe->sg_list;
	ssge.num_sge = swqe->wr.num_sge;
	sge = &ssge.sge;
	while (length) {
		u32 len = sge->length;

		if (len > length)
			len = length;
		if (len > sge->sge_length)
			len = sge->sge_length;
		BUG_ON(len == 0);
		qib_copy_sge(&qp->r_sge, sge->vaddr, len, 1);
		sge->vaddr += len;
		sge->length -= len;
		sge->sge_length -= len;
		if (sge->sge_length == 0) {
			if (--ssge.num_sge)
				*sge = *ssge.sg_list++;
		} else if (sge->length == 0 && sge->mr->lkey) {
			if (++sge->n >= RVT_SEGSZ) {
				if (++sge->m >= sge->mr->mapsz)
					break;
				sge->n = 0;
			}
			sge->vaddr =
				sge->mr->map[sge->m]->segs[sge->n].vaddr;
			sge->length =
				sge->mr->map[sge->m]->segs[sge->n].length;
		}
		length -= len;
	}
	rvt_put_ss(&qp->r_sge);
	if (!test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
		goto bail_unlock;
	wc.wr_id = qp->r_wr_id;
	wc.status = IB_WC_SUCCESS;
	wc.opcode = IB_WC_RECV;
	wc.qp = &qp->ibqp;
	wc.src_qp = sqp->ibqp.qp_num;
	wc.pkey_index = qp->ibqp.qp_type == IB_QPT_GSI ?
		swqe->ud_wr.pkey_index : 0;
	wc.slid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
				((1 << ppd->lmc) - 1));
	wc.sl = rdma_ah_get_sl(ah_attr);
	wc.dlid_path_bits = rdma_ah_get_dlid(ah_attr) & ((1 << ppd->lmc) - 1);
	wc.port_num = qp->port_num;
	/* Signal completion event if the solicited bit is set. */
	rvt_cq_enter(ibcq_to_rvtcq(qp->ibqp.recv_cq), &wc,
		     swqe->wr.send_flags & IB_SEND_SOLICITED);
	ibp->rvp.n_loop_pkts++;
bail_unlock:
	spin_unlock_irqrestore(&qp->r_lock, flags);
drop:
	rcu_read_unlock();
}