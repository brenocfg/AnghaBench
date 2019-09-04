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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int DEFAULT_KDETH_QP ; 
 int /*<<< orphan*/  RCV_BTH_QP ; 
 int RCV_BTH_QP_KDETH_QP_MASK ; 
 int RCV_BTH_QP_KDETH_QP_SHIFT ; 
 int /*<<< orphan*/  SEND_BTH_QP ; 
 int SEND_BTH_QP_KDETH_QP_MASK ; 
 int SEND_BTH_QP_KDETH_QP_SHIFT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int kdeth_qp ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_kdeth_qp(struct hfi1_devdata *dd)
{
	/* user changed the KDETH_QP */
	if (kdeth_qp != 0 && kdeth_qp >= 0xff) {
		/* out of range or illegal value */
		dd_dev_err(dd, "Invalid KDETH queue pair prefix, ignoring");
		kdeth_qp = 0;
	}
	if (kdeth_qp == 0)	/* not set, or failed range check */
		kdeth_qp = DEFAULT_KDETH_QP;

	write_csr(dd, SEND_BTH_QP,
		  (kdeth_qp & SEND_BTH_QP_KDETH_QP_MASK) <<
		  SEND_BTH_QP_KDETH_QP_SHIFT);

	write_csr(dd, RCV_BTH_QP,
		  (kdeth_qp & RCV_BTH_QP_KDETH_QP_MASK) <<
		  RCV_BTH_QP_KDETH_QP_SHIFT);
}