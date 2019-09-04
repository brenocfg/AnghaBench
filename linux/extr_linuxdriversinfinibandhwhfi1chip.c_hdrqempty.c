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
typedef  int u32 ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  dd; scalar_t__ rcvhdrtail_kvaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_HDR_HEAD ; 
 int RCV_HDR_HEAD_HEAD_SHIFT ; 
 int RCV_HDR_HEAD_HEAD_SMASK ; 
 int /*<<< orphan*/  RCV_HDR_TAIL ; 
 int get_rcvhdrtail (struct hfi1_ctxtdata*) ; 
 int read_uctxt_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 hdrqempty(struct hfi1_ctxtdata *rcd)
{
	u32 head, tail;

	head = (read_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_HEAD)
		& RCV_HDR_HEAD_HEAD_SMASK) >> RCV_HDR_HEAD_HEAD_SHIFT;

	if (rcd->rcvhdrtail_kvaddr)
		tail = get_rcvhdrtail(rcd);
	else
		tail = read_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_TAIL);

	return head == tail;
}