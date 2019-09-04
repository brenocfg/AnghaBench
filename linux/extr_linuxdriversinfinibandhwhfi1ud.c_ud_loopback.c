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
typedef  int /*<<< orphan*/  wc ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_17__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_22__ {scalar_t__ opcode; int send_flags; scalar_t__ num_sge; TYPE_2__ ex; } ;
struct TYPE_23__ {scalar_t__ remote_qkey; scalar_t__ pkey_index; int /*<<< orphan*/  ah; int /*<<< orphan*/  remote_qpn; } ;
struct rvt_swqe {scalar_t__ length; TYPE_7__ wr; TYPE_8__ ud_wr; struct rvt_sge* sg_list; } ;
struct rvt_sge {scalar_t__ length; scalar_t__ sge_length; scalar_t__ n; scalar_t__ m; TYPE_6__* mr; struct ib_grh* vaddr; } ;
struct rvt_sge_state {struct rvt_sge* sg_list; scalar_t__ num_sge; struct rvt_sge sge; } ;
struct TYPE_24__ {scalar_t__ qp_type; int qp_num; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  device; } ;
struct rvt_qp {size_t state; scalar_t__ qkey; int r_flags; scalar_t__ r_len; int /*<<< orphan*/  r_lock; TYPE_9__ ibqp; int /*<<< orphan*/  port_num; scalar_t__ s_pkey_index; int /*<<< orphan*/  r_wr_id; int /*<<< orphan*/  r_aflags; int /*<<< orphan*/  r_sge; struct hfi1_qp_priv* priv; } ;
struct rdma_ah_attr {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ byte_len; int src_qp; int slid; size_t sl; int dlid_path_bits; int /*<<< orphan*/  port_num; scalar_t__ pkey_index; TYPE_9__* qp; int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  wc_flags; TYPE_1__ ex; } ;
struct ib_grh {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  interface_id; } ;
struct TYPE_15__ {TYPE_3__ global; } ;
struct ib_global_route {scalar_t__ sgid_index; TYPE_12__ dgid; } ;
struct hfi1_qp_priv {scalar_t__ hdr_type; } ;
struct hfi1_pportdata {int lid; int lmc; int /*<<< orphan*/ * guids; } ;
struct TYPE_13__ {int /*<<< orphan*/  n_loop_pkts; int /*<<< orphan*/  n_pkt_drops; int /*<<< orphan*/  n_vl15_dropped; } ;
struct hfi1_ibport {TYPE_10__ rvp; int /*<<< orphan*/ * sl_to_sc; } ;
typedef  int /*<<< orphan*/  grh ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_21__ {scalar_t__ mapsz; TYPE_5__** map; scalar_t__ lkey; } ;
struct TYPE_20__ {TYPE_4__* segs; } ;
struct TYPE_19__ {scalar_t__ length; struct ib_grh* vaddr; } ;
struct TYPE_14__ {struct rdma_ah_attr attr; } ;

/* Variables and functions */
 scalar_t__ HFI1_PKT_TYPE_16B ; 
 size_t HFI1_PORT_GUID_INDEX ; 
 int IB_AH_GRH ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 int IB_QPT_UD ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IB_WC_GRH ; 
 int /*<<< orphan*/  IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RECV ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WITH_IMM ; 
 scalar_t__ IB_WR_SEND_WITH_IMM ; 
 scalar_t__ OPA_GID_INDEX ; 
 int RVT_PROCESS_RECV_OK ; 
 int RVT_R_REUSE_SGE ; 
 int /*<<< orphan*/  RVT_R_WRID_VALID ; 
 scalar_t__ RVT_SEGSZ ; 
 int U16_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_bad_pkey (struct hfi1_ibport*,int /*<<< orphan*/ ,size_t,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  hfi1_copy_sge (int /*<<< orphan*/ *,struct ib_grh*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  hfi1_get_pkey (struct hfi1_ibport*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_make_grh (struct hfi1_ibport*,struct ib_grh*,struct ib_global_route*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_is_opa_gid (TYPE_12__*) ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  ib_to_rvt (int /*<<< orphan*/ ) ; 
 TYPE_11__* ibah_to_rvtah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibcq_to_rvtcq (int /*<<< orphan*/ ) ; 
 int ingress_pkey_check (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 size_t rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rvt_cq_enter (int /*<<< orphan*/ ,struct ib_wc*,int) ; 
 int rvt_get_rwqe (struct rvt_qp*,int) ; 
 struct rvt_qp* rvt_lookup_qpn (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_put_ss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_rc_error (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_skip_sge (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hfi1_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ud_loopback(struct rvt_qp *sqp, struct rvt_swqe *swqe)
{
	struct hfi1_ibport *ibp = to_iport(sqp->ibqp.device, sqp->port_num);
	struct hfi1_pportdata *ppd;
	struct hfi1_qp_priv *priv = sqp->priv;
	struct rvt_qp *qp;
	struct rdma_ah_attr *ah_attr;
	unsigned long flags;
	struct rvt_sge_state ssge;
	struct rvt_sge *sge;
	struct ib_wc wc;
	u32 length;
	enum ib_qp_type sqptype, dqptype;

	rcu_read_lock();

	qp = rvt_lookup_qpn(ib_to_rvt(sqp->ibqp.device), &ibp->rvp,
			    swqe->ud_wr.remote_qpn);
	if (!qp) {
		ibp->rvp.n_pkt_drops++;
		rcu_read_unlock();
		return;
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
		u16 pkey;
		u32 slid;
		u8 sc5 = ibp->sl_to_sc[rdma_ah_get_sl(ah_attr)];

		pkey = hfi1_get_pkey(ibp, sqp->s_pkey_index);
		slid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
				   ((1 << ppd->lmc) - 1));
		if (unlikely(ingress_pkey_check(ppd, pkey, sc5,
						qp->s_pkey_index,
						slid, false))) {
			hfi1_bad_pkey(ibp, pkey,
				      rdma_ah_get_sl(ah_attr),
				      sqp->ibqp.qp_num, qp->ibqp.qp_num,
				      slid, rdma_ah_get_dlid(ah_attr));
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
			goto drop; /* silently drop per IBTA spec */
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
	if (qp->r_flags & RVT_R_REUSE_SGE) {
		qp->r_flags &= ~RVT_R_REUSE_SGE;
	} else {
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
		struct ib_global_route grd = *(rdma_ah_read_grh(ah_attr));

		/*
		 * For loopback packets with extended LIDs, the
		 * sgid_index in the GRH is 0 and the dgid is
		 * OPA GID of the sender. While creating a response
		 * to the loopback packet, IB core creates the new
		 * sgid_index from the DGID and that will be the
		 * OPA_GID_INDEX. The new dgid is from the sgid
		 * index and that will be in the IB GID format.
		 *
		 * We now have a case where the sent packet had a
		 * different sgid_index and dgid compared to the
		 * one that was received in response.
		 *
		 * Fix this inconsistency.
		 */
		if (priv->hdr_type == HFI1_PKT_TYPE_16B) {
			if (grd.sgid_index == 0)
				grd.sgid_index = OPA_GID_INDEX;

			if (ib_is_opa_gid(&grd.dgid))
				grd.dgid.global.interface_id =
				cpu_to_be64(ppd->guids[HFI1_PORT_GUID_INDEX]);
		}

		hfi1_make_grh(ibp, &grh, &grd, 0, 0);
		hfi1_copy_sge(&qp->r_sge, &grh,
			      sizeof(grh), true, false);
		wc.wc_flags |= IB_WC_GRH;
	} else {
		rvt_skip_sge(&qp->r_sge, sizeof(struct ib_grh), true);
	}
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
		WARN_ON_ONCE(len == 0);
		hfi1_copy_sge(&qp->r_sge, sge->vaddr, len, true, false);
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
	if (qp->ibqp.qp_type == IB_QPT_GSI || qp->ibqp.qp_type == IB_QPT_SMI) {
		if (sqp->ibqp.qp_type == IB_QPT_GSI ||
		    sqp->ibqp.qp_type == IB_QPT_SMI)
			wc.pkey_index = swqe->ud_wr.pkey_index;
		else
			wc.pkey_index = sqp->s_pkey_index;
	} else {
		wc.pkey_index = 0;
	}
	wc.slid = (ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
				   ((1 << ppd->lmc) - 1))) & U16_MAX;
	/* Check for loopback when the port lid is not set */
	if (wc.slid == 0 && sqp->ibqp.qp_type == IB_QPT_GSI)
		wc.slid = be16_to_cpu(IB_LID_PERMISSIVE);
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