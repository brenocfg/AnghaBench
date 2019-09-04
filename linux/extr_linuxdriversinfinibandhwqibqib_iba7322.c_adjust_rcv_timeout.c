#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qib_devdata {TYPE_1__* cspec; } ;
struct qib_ctxtdata {size_t ctxt; struct qib_devdata* dd; } ;
struct TYPE_2__ {int* rcvavail_timeout; } ;

/* Variables and functions */
 scalar_t__ kr_rcvavailtimeout ; 
 int min (int,int) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,scalar_t__,int) ; 
 int rcv_int_count ; 
 int rcv_int_timeout ; 

__attribute__((used)) static void adjust_rcv_timeout(struct qib_ctxtdata *rcd, int npkts)
{
	struct qib_devdata *dd = rcd->dd;
	u32 timeout = dd->cspec->rcvavail_timeout[rcd->ctxt];

	/*
	 * Dynamically adjust idle timeout on chip
	 * based on number of packets processed.
	 */
	if (npkts < rcv_int_count && timeout > 2)
		timeout >>= 1;
	else if (npkts >= rcv_int_count && timeout < rcv_int_timeout)
		timeout = min(timeout << 1, rcv_int_timeout);
	else
		return;

	dd->cspec->rcvavail_timeout[rcd->ctxt] = timeout;
	qib_write_kreg(dd, kr_rcvavailtimeout + rcd->ctxt, timeout);
}