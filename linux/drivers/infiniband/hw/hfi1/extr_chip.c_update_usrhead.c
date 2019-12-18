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
typedef  int u64 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int ctxt; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_EGR_INDEX_HEAD ; 
 int RCV_EGR_INDEX_HEAD_HEAD_MASK ; 
 int RCV_EGR_INDEX_HEAD_HEAD_SHIFT ; 
 int /*<<< orphan*/  RCV_HDR_HEAD ; 
 int RCV_HDR_HEAD_COUNTER_SHIFT ; 
 int RCV_HDR_HEAD_HEAD_MASK ; 
 int RCV_HDR_HEAD_HEAD_SHIFT ; 
 int /*<<< orphan*/  adjust_rcv_timeout (struct hfi1_ctxtdata*,int) ; 
 scalar_t__ rcv_intr_count ; 
 int /*<<< orphan*/  write_uctxt_csr (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int) ; 

void update_usrhead(struct hfi1_ctxtdata *rcd, u32 hd, u32 updegr, u32 egrhd,
		    u32 intr_adjust, u32 npkts)
{
	struct hfi1_devdata *dd = rcd->dd;
	u64 reg;
	u32 ctxt = rcd->ctxt;

	/*
	 * Need to write timeout register before updating RcvHdrHead to ensure
	 * that a new value is used when the HW decides to restart counting.
	 */
	if (intr_adjust)
		adjust_rcv_timeout(rcd, npkts);
	if (updegr) {
		reg = (egrhd & RCV_EGR_INDEX_HEAD_HEAD_MASK)
			<< RCV_EGR_INDEX_HEAD_HEAD_SHIFT;
		write_uctxt_csr(dd, ctxt, RCV_EGR_INDEX_HEAD, reg);
	}
	reg = ((u64)rcv_intr_count << RCV_HDR_HEAD_COUNTER_SHIFT) |
		(((u64)hd & RCV_HDR_HEAD_HEAD_MASK)
			<< RCV_HDR_HEAD_HEAD_SHIFT);
	write_uctxt_csr(dd, ctxt, RCV_HDR_HEAD, reg);
}