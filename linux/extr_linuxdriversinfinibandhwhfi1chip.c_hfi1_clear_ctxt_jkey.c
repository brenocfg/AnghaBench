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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ctxt; TYPE_1__* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RCV_KEY_CTRL ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_ENABLE ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_JOB_KEY ; 
 int /*<<< orphan*/  is_ax (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  read_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfi1_clear_ctxt_jkey(struct hfi1_devdata *dd, struct hfi1_ctxtdata *rcd)
{
	u8 hw_ctxt;
	u64 reg;

	if (!rcd || !rcd->sc)
		return -EINVAL;

	hw_ctxt = rcd->sc->hw_context;
	write_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_JOB_KEY, 0);
	/*
	 * Disable send-side J_KEY integrity check, unless this is A0 h/w.
	 * This check would not have been enabled for A0 h/w, see
	 * set_ctxt_jkey().
	 */
	if (!is_ax(dd)) {
		reg = read_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
		reg &= ~SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK;
		write_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);
	}
	/* Turn off the J_KEY on the receive side */
	write_kctxt_csr(dd, rcd->ctxt, RCV_KEY_CTRL, 0);

	return 0;
}