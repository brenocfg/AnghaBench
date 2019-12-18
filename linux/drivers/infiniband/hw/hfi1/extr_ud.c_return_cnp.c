#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct send_context {int dummy; } ;
struct rvt_qp {int /*<<< orphan*/  srate_mbps; } ;
struct pio_buf {int dummy; } ;
struct ib_other_headers {void** bth; } ;
struct ib_grh {int hop_limit; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; int /*<<< orphan*/  paylen; int /*<<< orphan*/  version_tclass_flow; } ;
struct hfi1_pportdata {TYPE_3__* dd; } ;
struct TYPE_7__ {struct ib_other_headers oth; struct ib_grh grh; } ;
struct TYPE_8__ {struct ib_other_headers oth; TYPE_1__ l; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct hfi1_opa_header {TYPE_6__ ibh; int /*<<< orphan*/  hdr_type; } ;
struct hfi1_ibport {size_t* sc_to_sl; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* pio_inline_send ) (TYPE_3__*,struct pio_buf*,int,struct hfi1_opa_header*,int) ;} ;

/* Variables and functions */
 size_t HFI1_LRH_BTH ; 
 size_t HFI1_LRH_GRH ; 
 int /*<<< orphan*/  HFI1_PKT_TYPE_9B ; 
 int IB_BECN_SHIFT ; 
 int IB_OPCODE_CNP ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct pio_buf*) ; 
 int LRH_9B_DWORDS ; 
 int PBC_DC_INFO_SHIFT ; 
 int SIZE_OF_CRC ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int create_pbc (struct hfi1_pportdata*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hfi1_make_ib_hdr (TYPE_6__*,size_t,int,int,int) ; 
 int ib_is_sc5 (size_t) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 struct send_context* qp_to_send_context (struct rvt_qp*,size_t) ; 
 struct pio_buf* sc_buffer_alloc (struct send_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sc_to_vlt (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct pio_buf*,int,struct hfi1_opa_header*,int) ; 
 int /*<<< orphan*/  trace_pio_output_ibhdr (TYPE_3__*,struct hfi1_opa_header*,size_t) ; 

void return_cnp(struct hfi1_ibport *ibp, struct rvt_qp *qp, u32 remote_qpn,
		u16 pkey, u32 slid, u32 dlid, u8 sc5,
		const struct ib_grh *old_grh)
{
	u64 pbc, pbc_flags = 0;
	u32 bth0, plen, vl, hwords = 5;
	u16 lrh0;
	u8 sl = ibp->sc_to_sl[sc5];
	struct hfi1_opa_header hdr;
	struct ib_other_headers *ohdr;
	struct pio_buf *pbuf;
	struct send_context *ctxt = qp_to_send_context(qp, sc5);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	hdr.hdr_type = HFI1_PKT_TYPE_9B;
	if (old_grh) {
		struct ib_grh *grh = &hdr.ibh.u.l.grh;

		grh->version_tclass_flow = old_grh->version_tclass_flow;
		grh->paylen = cpu_to_be16(
			(hwords - LRH_9B_DWORDS + SIZE_OF_CRC) << 2);
		grh->hop_limit = 0xff;
		grh->sgid = old_grh->dgid;
		grh->dgid = old_grh->sgid;
		ohdr = &hdr.ibh.u.l.oth;
		lrh0 = HFI1_LRH_GRH;
		hwords += sizeof(struct ib_grh) / sizeof(u32);
	} else {
		ohdr = &hdr.ibh.u.oth;
		lrh0 = HFI1_LRH_BTH;
	}

	lrh0 |= (sc5 & 0xf) << 12 | sl << 4;

	bth0 = pkey | (IB_OPCODE_CNP << 24);
	ohdr->bth[0] = cpu_to_be32(bth0);

	ohdr->bth[1] = cpu_to_be32(remote_qpn | (1 << IB_BECN_SHIFT));
	ohdr->bth[2] = 0; /* PSN 0 */

	hfi1_make_ib_hdr(&hdr.ibh, lrh0, hwords + SIZE_OF_CRC, dlid, slid);
	plen = 2 /* PBC */ + hwords;
	pbc_flags |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);
	vl = sc_to_vlt(ppd->dd, sc5);
	pbc = create_pbc(ppd, pbc_flags, qp->srate_mbps, vl, plen);
	if (ctxt) {
		pbuf = sc_buffer_alloc(ctxt, plen, NULL, NULL);
		if (!IS_ERR_OR_NULL(pbuf)) {
			trace_pio_output_ibhdr(ppd->dd, &hdr, sc5);
			ppd->dd->pio_inline_send(ppd->dd, pbuf, pbc,
						 &hdr, hwords);
		}
	}
}