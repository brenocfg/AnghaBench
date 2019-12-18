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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int qp_type; } ;
struct rvt_qp {size_t state; int remote_qpn; TYPE_3__ ibqp; int /*<<< orphan*/  r_lock; } ;
struct rvt_dev_info {int dummy; } ;
struct ib_grh {scalar_t__ next_hdr; int /*<<< orphan*/  version_tclass_flow; } ;
struct TYPE_5__ {struct ib_grh grh; int /*<<< orphan*/  oth; } ;
struct TYPE_6__ {TYPE_1__ l; int /*<<< orphan*/  oth; } ;
struct ib_header {TYPE_2__ u; } ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct hfi1_packet {int rhf; scalar_t__ etype; int /*<<< orphan*/ * ohdr; void* ebuf; struct ib_grh* grh; struct ib_header* hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  n_pkt_drops; } ;
struct hfi1_ibport {scalar_t__* sc_to_sl; TYPE_4__ rvp; } ;
struct hfi1_ibdev {struct rvt_dev_info rdi; } ;
struct hfi1_devdata {struct hfi1_ibdev verbs_dev; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ HFI1_LRH_BTH ; 
 scalar_t__ HFI1_LRH_GRH ; 
 scalar_t__ IB_CC_SVCTYPE_UC ; 
 scalar_t__ IB_CC_SVCTYPE_UD ; 
 scalar_t__ IB_GRH_NEXT_HDR ; 
 int IB_GRH_VERSION ; 
 int IB_GRH_VERSION_SHIFT ; 
 int /*<<< orphan*/  IB_MULTICAST_LID_BASE ; 
 scalar_t__ IB_OPCODE_CNP ; 
#define  IB_QPT_RC 131 
#define  IB_QPT_UC 130 
#define  IB_QPT_UD 129 
 int RHF_DC_ERR ; 
 int RHF_ICRC_ERR ; 
 scalar_t__ RHF_RCV_TYPE_BYPASS ; 
 int RHF_RCV_TYPE_ERR_SMASK ; 
#define  RHF_RTE_ERROR_OP_CODE_ERR 128 
 int RHF_TID_ERR ; 
 int RVT_PROCESS_RECV_OK ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ hfi1_9B_get_sc5 (struct ib_header*,int) ; 
 scalar_t__ hfi1_dbg_fault_suppress_err (struct hfi1_ibdev*) ; 
 int /*<<< orphan*/  hfi1_rc_hdrerr (struct hfi1_ctxtdata*,struct hfi1_packet*,struct rvt_qp*) ; 
 scalar_t__ ib_bth_get_opcode (int /*<<< orphan*/ *) ; 
 int ib_bth_get_qpn (int /*<<< orphan*/ *) ; 
 int ib_get_dlid (struct ib_header*) ; 
 scalar_t__ ib_get_lnh (struct ib_header*) ; 
 int /*<<< orphan*/  ib_get_slid (struct ib_header*) ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  process_becn (struct hfi1_pportdata*,scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 struct hfi1_ibport* rcd_to_iport (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rhf_pkt_len (int) ; 
 int rhf_rcv_type_err (int) ; 
 int /*<<< orphan*/  rhf_use_egr_bfr (int) ; 
 struct rvt_qp* rvt_lookup_qpn (struct rvt_dev_info*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rcv_hdrerr(struct hfi1_ctxtdata *rcd, struct hfi1_pportdata *ppd,
		       struct hfi1_packet *packet)
{
	struct ib_header *rhdr = packet->hdr;
	u32 rte = rhf_rcv_type_err(packet->rhf);
	u32 mlid_base;
	struct hfi1_ibport *ibp = rcd_to_iport(rcd);
	struct hfi1_devdata *dd = ppd->dd;
	struct hfi1_ibdev *verbs_dev = &dd->verbs_dev;
	struct rvt_dev_info *rdi = &verbs_dev->rdi;

	if ((packet->rhf & RHF_DC_ERR) &&
	    hfi1_dbg_fault_suppress_err(verbs_dev))
		return;

	if (packet->rhf & RHF_ICRC_ERR)
		return;

	if (packet->etype == RHF_RCV_TYPE_BYPASS) {
		goto drop;
	} else {
		u8 lnh = ib_get_lnh(rhdr);

		mlid_base = be16_to_cpu(IB_MULTICAST_LID_BASE);
		if (lnh == HFI1_LRH_BTH) {
			packet->ohdr = &rhdr->u.oth;
		} else if (lnh == HFI1_LRH_GRH) {
			packet->ohdr = &rhdr->u.l.oth;
			packet->grh = &rhdr->u.l.grh;
		} else {
			goto drop;
		}
	}

	if (packet->rhf & RHF_TID_ERR) {
		/* For TIDERR and RC QPs preemptively schedule a NAK */
		u32 tlen = rhf_pkt_len(packet->rhf); /* in bytes */
		u32 dlid = ib_get_dlid(rhdr);
		u32 qp_num;

		/* Sanity check packet */
		if (tlen < 24)
			goto drop;

		/* Check for GRH */
		if (packet->grh) {
			u32 vtf;
			struct ib_grh *grh = packet->grh;

			if (grh->next_hdr != IB_GRH_NEXT_HDR)
				goto drop;
			vtf = be32_to_cpu(grh->version_tclass_flow);
			if ((vtf >> IB_GRH_VERSION_SHIFT) != IB_GRH_VERSION)
				goto drop;
		}

		/* Get the destination QP number. */
		qp_num = ib_bth_get_qpn(packet->ohdr);
		if (dlid < mlid_base) {
			struct rvt_qp *qp;
			unsigned long flags;

			rcu_read_lock();
			qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
			if (!qp) {
				rcu_read_unlock();
				goto drop;
			}

			/*
			 * Handle only RC QPs - for other QP types drop error
			 * packet.
			 */
			spin_lock_irqsave(&qp->r_lock, flags);

			/* Check for valid receive state. */
			if (!(ib_rvt_state_ops[qp->state] &
			      RVT_PROCESS_RECV_OK)) {
				ibp->rvp.n_pkt_drops++;
			}

			switch (qp->ibqp.qp_type) {
			case IB_QPT_RC:
				hfi1_rc_hdrerr(rcd, packet, qp);
				break;
			default:
				/* For now don't handle any other QP types */
				break;
			}

			spin_unlock_irqrestore(&qp->r_lock, flags);
			rcu_read_unlock();
		} /* Unicast QP */
	} /* Valid packet with TIDErr */

	/* handle "RcvTypeErr" flags */
	switch (rte) {
	case RHF_RTE_ERROR_OP_CODE_ERR:
	{
		void *ebuf = NULL;
		u8 opcode;

		if (rhf_use_egr_bfr(packet->rhf))
			ebuf = packet->ebuf;

		if (!ebuf)
			goto drop; /* this should never happen */

		opcode = ib_bth_get_opcode(packet->ohdr);
		if (opcode == IB_OPCODE_CNP) {
			/*
			 * Only in pre-B0 h/w is the CNP_OPCODE handled
			 * via this code path.
			 */
			struct rvt_qp *qp = NULL;
			u32 lqpn, rqpn;
			u16 rlid;
			u8 svc_type, sl, sc5;

			sc5 = hfi1_9B_get_sc5(rhdr, packet->rhf);
			sl = ibp->sc_to_sl[sc5];

			lqpn = ib_bth_get_qpn(packet->ohdr);
			rcu_read_lock();
			qp = rvt_lookup_qpn(rdi, &ibp->rvp, lqpn);
			if (!qp) {
				rcu_read_unlock();
				goto drop;
			}

			switch (qp->ibqp.qp_type) {
			case IB_QPT_UD:
				rlid = 0;
				rqpn = 0;
				svc_type = IB_CC_SVCTYPE_UD;
				break;
			case IB_QPT_UC:
				rlid = ib_get_slid(rhdr);
				rqpn = qp->remote_qpn;
				svc_type = IB_CC_SVCTYPE_UC;
				break;
			default:
				rcu_read_unlock();
				goto drop;
			}

			process_becn(ppd, sl, rlid, lqpn, rqpn, svc_type);
			rcu_read_unlock();
		}

		packet->rhf &= ~RHF_RCV_TYPE_ERR_SMASK;
		break;
	}
	default:
		break;
	}

drop:
	return;
}