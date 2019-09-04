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
typedef  int u64 ;
typedef  int u16 ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  flags; TYPE_1__* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_PERM_JKEY ; 
 int EINVAL ; 
 scalar_t__ HFI1_CAP_KGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCV_KEY_CTRL ; 
 int RCV_KEY_CTRL_JOB_KEY_ENABLE_SMASK ; 
 int RCV_KEY_CTRL_JOB_KEY_VALUE_MASK ; 
 int RCV_KEY_CTRL_JOB_KEY_VALUE_SHIFT ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_ENABLE ; 
 int SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_JOB_KEY ; 
 int SEND_CTXT_CHECK_JOB_KEY_ALLOW_PERMISSIVE_SMASK ; 
 int SEND_CTXT_CHECK_JOB_KEY_MASK_SMASK ; 
 int SEND_CTXT_CHECK_JOB_KEY_VALUE_MASK ; 
 int SEND_CTXT_CHECK_JOB_KEY_VALUE_SHIFT ; 
 int /*<<< orphan*/  is_ax (struct hfi1_devdata*) ; 
 int read_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hfi1_set_ctxt_jkey(struct hfi1_devdata *dd, struct hfi1_ctxtdata *rcd,
		       u16 jkey)
{
	u8 hw_ctxt;
	u64 reg;

	if (!rcd || !rcd->sc)
		return -EINVAL;

	hw_ctxt = rcd->sc->hw_context;
	reg = SEND_CTXT_CHECK_JOB_KEY_MASK_SMASK | /* mask is always 1's */
		((jkey & SEND_CTXT_CHECK_JOB_KEY_VALUE_MASK) <<
		 SEND_CTXT_CHECK_JOB_KEY_VALUE_SHIFT);
	/* JOB_KEY_ALLOW_PERMISSIVE is not allowed by default */
	if (HFI1_CAP_KGET_MASK(rcd->flags, ALLOW_PERM_JKEY))
		reg |= SEND_CTXT_CHECK_JOB_KEY_ALLOW_PERMISSIVE_SMASK;
	write_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_JOB_KEY, reg);
	/*
	 * Enable send-side J_KEY integrity check, unless this is A0 h/w
	 */
	if (!is_ax(dd)) {
		reg = read_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE);
		reg |= SEND_CTXT_CHECK_ENABLE_CHECK_JOB_KEY_SMASK;
		write_kctxt_csr(dd, hw_ctxt, SEND_CTXT_CHECK_ENABLE, reg);
	}

	/* Enable J_KEY check on receive context. */
	reg = RCV_KEY_CTRL_JOB_KEY_ENABLE_SMASK |
		((jkey & RCV_KEY_CTRL_JOB_KEY_VALUE_MASK) <<
		 RCV_KEY_CTRL_JOB_KEY_VALUE_SHIFT);
	write_kctxt_csr(dd, rcd->ctxt, RCV_KEY_CTRL, reg);

	return 0;
}