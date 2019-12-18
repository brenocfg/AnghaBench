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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct send_context {int dummy; } ;
struct rvt_qp {int /*<<< orphan*/  srate_mbps; } ;
struct pio_buf {int dummy; } ;
struct ib_other_headers {void** bth; } ;
struct ib_grh {int hop_limit; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; int /*<<< orphan*/  paylen; int /*<<< orphan*/  version_tclass_flow; } ;
struct hfi1_pportdata {TYPE_3__* dd; } ;
struct TYPE_7__ {struct ib_other_headers oth; struct ib_grh grh; } ;
struct TYPE_8__ {struct ib_other_headers oth; TYPE_1__ l; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct hfi1_opa_header {TYPE_6__ opah; int /*<<< orphan*/  hdr_type; } ;
struct hfi1_ibport {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* pio_inline_send ) (TYPE_3__*,struct pio_buf*,int,struct hfi1_opa_header*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_PKT_TYPE_16B ; 
 int IB_OPCODE_CNP ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct pio_buf*) ; 
 int LRH_16B_DWORDS ; 
 int /*<<< orphan*/  OPA_16B_L4_IB_GLOBAL ; 
 int /*<<< orphan*/  OPA_16B_L4_IB_LOCAL ; 
 int PBC_INSERT_BYPASS_ICRC ; 
 int PBC_PACKET_BYPASS ; 
 int SIZE_OF_CRC ; 
 int SIZE_OF_LT ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int create_pbc (struct hfi1_pportdata*,int,int /*<<< orphan*/ ,int,int) ; 
 int hfi1_get_16b_padding (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_make_16b_hdr (TYPE_6__*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 struct send_context* qp_to_send_context (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct pio_buf* sc_buffer_alloc (struct send_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sc_to_vlt (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct pio_buf*,int,struct hfi1_opa_header*,int) ; 
 int /*<<< orphan*/  trace_pio_output_ibhdr (TYPE_3__*,struct hfi1_opa_header*,int /*<<< orphan*/ ) ; 

void return_cnp_16B(struct hfi1_ibport *ibp, struct rvt_qp *qp,
		    u32 remote_qpn, u16 pkey, u32 slid, u32 dlid,
		    u8 sc5, const struct ib_grh *old_grh)
{
	u64 pbc, pbc_flags = 0;
	u32 bth0, plen, vl, hwords = 7;
	u16 len;
	u8 l4;
	struct hfi1_opa_header hdr;
	struct ib_other_headers *ohdr;
	struct pio_buf *pbuf;
	struct send_context *ctxt = qp_to_send_context(qp, sc5);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 nwords;

	hdr.hdr_type = HFI1_PKT_TYPE_16B;
	/* Populate length */
	nwords = ((hfi1_get_16b_padding(hwords << 2, 0) +
		   SIZE_OF_LT) >> 2) + SIZE_OF_CRC;
	if (old_grh) {
		struct ib_grh *grh = &hdr.opah.u.l.grh;

		grh->version_tclass_flow = old_grh->version_tclass_flow;
		grh->paylen = cpu_to_be16(
			(hwords - LRH_16B_DWORDS + nwords) << 2);
		grh->hop_limit = 0xff;
		grh->sgid = old_grh->dgid;
		grh->dgid = old_grh->sgid;
		ohdr = &hdr.opah.u.l.oth;
		l4 = OPA_16B_L4_IB_GLOBAL;
		hwords += sizeof(struct ib_grh) / sizeof(u32);
	} else {
		ohdr = &hdr.opah.u.oth;
		l4 = OPA_16B_L4_IB_LOCAL;
	}

	/* BIT 16 to 19 is TVER. Bit 20 to 22 is pad cnt */
	bth0 = (IB_OPCODE_CNP << 24) | (1 << 16) |
	       (hfi1_get_16b_padding(hwords << 2, 0) << 20);
	ohdr->bth[0] = cpu_to_be32(bth0);

	ohdr->bth[1] = cpu_to_be32(remote_qpn);
	ohdr->bth[2] = 0; /* PSN 0 */

	/* Convert dwords to flits */
	len = (hwords + nwords) >> 1;
	hfi1_make_16b_hdr(&hdr.opah, slid, dlid, len, pkey, 1, 0, l4, sc5);

	plen = 2 /* PBC */ + hwords + nwords;
	pbc_flags |= PBC_PACKET_BYPASS | PBC_INSERT_BYPASS_ICRC;
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