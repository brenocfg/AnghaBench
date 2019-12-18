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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int qp_type; int /*<<< orphan*/  qp_num; } ;
struct rvt_qp {TYPE_2__ ibqp; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  remote_ah_attr; } ;
struct ib_header {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_packet {int /*<<< orphan*/  rhf; struct rvt_qp* qp; struct ib_header* hdr; int /*<<< orphan*/  rcd; } ;
struct TYPE_3__ {int /*<<< orphan*/  n_pkt_drops; } ;
struct hfi1_ibport {size_t* sc_to_sl; TYPE_1__ rvp; } ;

/* Variables and functions */
 size_t IB_CC_SVCTYPE_RC ; 
 size_t IB_CC_SVCTYPE_UC ; 
 size_t IB_CC_SVCTYPE_UD ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 size_t hfi1_9B_get_sc5 (struct ib_header*,int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  process_becn (struct hfi1_pportdata*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct hfi1_ibport* rcd_to_iport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 

void hfi1_cnp_rcv(struct hfi1_packet *packet)
{
	struct hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	struct ib_header *hdr = packet->hdr;
	struct rvt_qp *qp = packet->qp;
	u32 lqpn, rqpn = 0;
	u16 rlid = 0;
	u8 sl, sc5, svc_type;

	switch (packet->qp->ibqp.qp_type) {
	case IB_QPT_UC:
		rlid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		rqpn = qp->remote_qpn;
		svc_type = IB_CC_SVCTYPE_UC;
		break;
	case IB_QPT_RC:
		rlid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		rqpn = qp->remote_qpn;
		svc_type = IB_CC_SVCTYPE_RC;
		break;
	case IB_QPT_SMI:
	case IB_QPT_GSI:
	case IB_QPT_UD:
		svc_type = IB_CC_SVCTYPE_UD;
		break;
	default:
		ibp->rvp.n_pkt_drops++;
		return;
	}

	sc5 = hfi1_9B_get_sc5(hdr, packet->rhf);
	sl = ibp->sc_to_sl[sc5];
	lqpn = qp->ibqp.qp_num;

	process_becn(ppd, sl, rlid, lqpn, rqpn, svc_type);
}