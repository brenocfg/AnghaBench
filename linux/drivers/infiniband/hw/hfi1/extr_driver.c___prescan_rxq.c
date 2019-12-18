#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct rvt_qp {int dummy; } ;
struct rvt_dev_info {int dummy; } ;
struct ps_mdata {int ps_head; } ;
struct TYPE_10__ {int /*<<< orphan*/ * bth; } ;
struct TYPE_8__ {int /*<<< orphan*/  grh; TYPE_5__ oth; } ;
struct TYPE_9__ {TYPE_3__ l; TYPE_5__ oth; } ;
struct ib_header {TYPE_4__ u; } ;
struct hfi1_packet {TYPE_5__* ohdr; int /*<<< orphan*/ * grh; struct ib_header* hdr; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ibport {int /*<<< orphan*/  rvp; } ;
struct hfi1_ctxtdata {int rhf_offset; TYPE_2__* dd; scalar_t__ rcvhdrq; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {struct rvt_dev_info rdi; } ;
struct TYPE_7__ {TYPE_1__ verbs_dev; } ;

/* Variables and functions */
 scalar_t__ HFI1_LRH_BTH ; 
 scalar_t__ HFI1_LRH_GRH ; 
 scalar_t__ IB_BECN_SMASK ; 
 scalar_t__ IB_FECN_SMASK ; 
 scalar_t__ RHF_RCV_TYPE_IB ; 
 scalar_t__ RVT_QPN_MASK ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 struct ib_header* hfi1_get_msgheader (struct hfi1_ctxtdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_may_ecn (struct hfi1_packet*) ; 
 int /*<<< orphan*/  hfi1_process_ecn_slowpath (struct rvt_qp*,struct hfi1_packet*,int) ; 
 scalar_t__ ib_get_lnh (struct ib_header*) ; 
 int /*<<< orphan*/  init_ps_mdata (struct ps_mdata*,struct hfi1_packet*) ; 
 scalar_t__ ps_done (struct ps_mdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata*) ; 
 scalar_t__ ps_skip (struct ps_mdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata*) ; 
 struct hfi1_ibport* rcd_to_iport (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rhf_rcv_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhf_to_cpu (int /*<<< orphan*/ *) ; 
 struct rvt_qp* rvt_lookup_qpn (struct rvt_dev_info*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  update_ps_mdata (struct ps_mdata*,struct hfi1_ctxtdata*) ; 

__attribute__((used)) static void __prescan_rxq(struct hfi1_packet *packet)
{
	struct hfi1_ctxtdata *rcd = packet->rcd;
	struct ps_mdata mdata;

	init_ps_mdata(&mdata, packet);

	while (1) {
		struct hfi1_ibport *ibp = rcd_to_iport(rcd);
		__le32 *rhf_addr = (__le32 *)rcd->rcvhdrq + mdata.ps_head +
					 packet->rcd->rhf_offset;
		struct rvt_qp *qp;
		struct ib_header *hdr;
		struct rvt_dev_info *rdi = &rcd->dd->verbs_dev.rdi;
		u64 rhf = rhf_to_cpu(rhf_addr);
		u32 etype = rhf_rcv_type(rhf), qpn, bth1;
		u8 lnh;

		if (ps_done(&mdata, rhf, rcd))
			break;

		if (ps_skip(&mdata, rhf, rcd))
			goto next;

		if (etype != RHF_RCV_TYPE_IB)
			goto next;

		packet->hdr = hfi1_get_msgheader(packet->rcd, rhf_addr);
		hdr = packet->hdr;
		lnh = ib_get_lnh(hdr);

		if (lnh == HFI1_LRH_BTH) {
			packet->ohdr = &hdr->u.oth;
			packet->grh = NULL;
		} else if (lnh == HFI1_LRH_GRH) {
			packet->ohdr = &hdr->u.l.oth;
			packet->grh = &hdr->u.l.grh;
		} else {
			goto next; /* just in case */
		}

		if (!hfi1_may_ecn(packet))
			goto next;

		bth1 = be32_to_cpu(packet->ohdr->bth[1]);
		qpn = bth1 & RVT_QPN_MASK;
		rcu_read_lock();
		qp = rvt_lookup_qpn(rdi, &ibp->rvp, qpn);

		if (!qp) {
			rcu_read_unlock();
			goto next;
		}

		hfi1_process_ecn_slowpath(qp, packet, true);
		rcu_read_unlock();

		/* turn off BECN, FECN */
		bth1 &= ~(IB_FECN_SMASK | IB_BECN_SMASK);
		packet->ohdr->bth[1] = cpu_to_be32(bth1);
next:
		update_ps_mdata(&mdata, rcd);
	}
}