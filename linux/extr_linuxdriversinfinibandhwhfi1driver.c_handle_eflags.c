#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_packet {int rhf; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  dd; int /*<<< orphan*/  ppd; } ;

/* Variables and functions */
 int RHF_DC_ERR ; 
 int RHF_DC_UNC_ERR ; 
 int RHF_ECC_ERR ; 
 int RHF_ICRC_ERR ; 
 int RHF_K_HDR_LEN_ERR ; 
 int RHF_LEN_ERR ; 
 int RHF_TID_ERR ; 
 int RHF_VCRC_ERR ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_hdrerr (struct hfi1_ctxtdata*,int /*<<< orphan*/ ,struct hfi1_packet*) ; 
 scalar_t__ rhf_err_flags (int) ; 
 int /*<<< orphan*/  rhf_rcv_type_err (int) ; 

void handle_eflags(struct hfi1_packet *packet)
{
	struct hfi1_ctxtdata *rcd = packet->rcd;
	u32 rte = rhf_rcv_type_err(packet->rhf);

	rcv_hdrerr(rcd, rcd->ppd, packet);
	if (rhf_err_flags(packet->rhf))
		dd_dev_err(rcd->dd,
			   "receive context %d: rhf 0x%016llx, errs [ %s%s%s%s%s%s%s%s] rte 0x%x\n",
			   rcd->ctxt, packet->rhf,
			   packet->rhf & RHF_K_HDR_LEN_ERR ? "k_hdr_len " : "",
			   packet->rhf & RHF_DC_UNC_ERR ? "dc_unc " : "",
			   packet->rhf & RHF_DC_ERR ? "dc " : "",
			   packet->rhf & RHF_TID_ERR ? "tid " : "",
			   packet->rhf & RHF_LEN_ERR ? "len " : "",
			   packet->rhf & RHF_ECC_ERR ? "ecc " : "",
			   packet->rhf & RHF_VCRC_ERR ? "vcrc " : "",
			   packet->rhf & RHF_ICRC_ERR ? "icrc " : "",
			   rte);
}