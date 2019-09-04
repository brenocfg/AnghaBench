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
typedef  scalar_t__ u32 ;
struct hfi1_devdata {scalar_t__ rcv_intr_timeout_csr; } ;
struct hfi1_ctxtdata {scalar_t__ rcvavail_timeout; int /*<<< orphan*/  ctxt; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_AVAIL_TIME_OUT ; 
 int RCV_AVAIL_TIME_OUT_TIME_OUT_RELOAD_SHIFT ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ rcv_intr_count ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adjust_rcv_timeout(struct hfi1_ctxtdata *rcd, u32 npkts)
{
	struct hfi1_devdata *dd = rcd->dd;
	u32 timeout = rcd->rcvavail_timeout;

	/*
	 * This algorithm doubles or halves the timeout depending on whether
	 * the number of packets received in this interrupt were less than or
	 * greater equal the interrupt count.
	 *
	 * The calculations below do not allow a steady state to be achieved.
	 * Only at the endpoints it is possible to have an unchanging
	 * timeout.
	 */
	if (npkts < rcv_intr_count) {
		/*
		 * Not enough packets arrived before the timeout, adjust
		 * timeout downward.
		 */
		if (timeout < 2) /* already at minimum? */
			return;
		timeout >>= 1;
	} else {
		/*
		 * More than enough packets arrived before the timeout, adjust
		 * timeout upward.
		 */
		if (timeout >= dd->rcv_intr_timeout_csr) /* already at max? */
			return;
		timeout = min(timeout << 1, dd->rcv_intr_timeout_csr);
	}

	rcd->rcvavail_timeout = timeout;
	/*
	 * timeout cannot be larger than rcv_intr_timeout_csr which has already
	 * been verified to be in range
	 */
	write_kctxt_csr(dd, rcd->ctxt, RCV_AVAIL_TIME_OUT,
			(u64)timeout <<
			RCV_AVAIL_TIME_OUT_TIME_OUT_RELOAD_SHIFT);
}