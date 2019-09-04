#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {unsigned long long rcvctrl; unsigned long long ctxtcnt; int flags; int rhdrhead_intr_off; int first_user_ctxt; unsigned int cfgctxts; TYPE_2__* cspec; TYPE_1__** rcd; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcvmod_lock; int /*<<< orphan*/  dummy_hdrq_phys; int /*<<< orphan*/  dummy_hdrq; } ;
struct TYPE_3__ {int head; int /*<<< orphan*/  rcvhdrq_phys; int /*<<< orphan*/  rcvhdrqtailaddr_phys; } ;

/* Variables and functions */
 unsigned long long IBA6120_R_PKEY_DIS_SHIFT ; 
 int /*<<< orphan*/  PortEnable ; 
 int QIB_NODMA_RTAIL ; 
 unsigned int QIB_RCVCTRL_CTXT_DIS ; 
 unsigned int QIB_RCVCTRL_CTXT_ENB ; 
 unsigned int QIB_RCVCTRL_INTRAVAIL_DIS ; 
 unsigned int QIB_RCVCTRL_INTRAVAIL_ENB ; 
 unsigned int QIB_RCVCTRL_PKEY_DIS ; 
 unsigned int QIB_RCVCTRL_PKEY_ENB ; 
 unsigned int QIB_RCVCTRL_TAILUPD_DIS ; 
 unsigned int QIB_RCVCTRL_TAILUPD_ENB ; 
 int QLOGIC_IB_R_INTRAVAIL_SHIFT ; 
 unsigned long long QLOGIC_IB_R_TAILUPD_SHIFT ; 
 int /*<<< orphan*/  RcvCtrl ; 
 int SYM_LSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_dummy_hdrq (struct qib_devdata*) ; 
 int /*<<< orphan*/  kr_rcvctrl ; 
 int /*<<< orphan*/  kr_rcvhdraddr ; 
 int /*<<< orphan*/  kr_rcvhdrtailaddr ; 
 int qib_read_ureg32 (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_write_kreg_ctxt (struct qib_devdata*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_ureg (struct qib_devdata*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ur_rcvegrindexhead ; 
 int /*<<< orphan*/  ur_rcvegrindextail ; 
 int /*<<< orphan*/  ur_rcvhdrhead ; 
 int /*<<< orphan*/  ur_rcvhdrtail ; 

__attribute__((used)) static void rcvctrl_6120_mod(struct qib_pportdata *ppd, unsigned int op,
			     int ctxt)
{
	struct qib_devdata *dd = ppd->dd;
	u64 mask, val;
	unsigned long flags;

	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);

	if (op & QIB_RCVCTRL_TAILUPD_ENB)
		dd->rcvctrl |= (1ULL << QLOGIC_IB_R_TAILUPD_SHIFT);
	if (op & QIB_RCVCTRL_TAILUPD_DIS)
		dd->rcvctrl &= ~(1ULL << QLOGIC_IB_R_TAILUPD_SHIFT);
	if (op & QIB_RCVCTRL_PKEY_ENB)
		dd->rcvctrl &= ~(1ULL << IBA6120_R_PKEY_DIS_SHIFT);
	if (op & QIB_RCVCTRL_PKEY_DIS)
		dd->rcvctrl |= (1ULL << IBA6120_R_PKEY_DIS_SHIFT);
	if (ctxt < 0)
		mask = (1ULL << dd->ctxtcnt) - 1;
	else
		mask = (1ULL << ctxt);
	if (op & QIB_RCVCTRL_CTXT_ENB) {
		/* always done for specific ctxt */
		dd->rcvctrl |= (mask << SYM_LSB(RcvCtrl, PortEnable));
		if (!(dd->flags & QIB_NODMA_RTAIL))
			dd->rcvctrl |= 1ULL << QLOGIC_IB_R_TAILUPD_SHIFT;
		/* Write these registers before the context is enabled. */
		qib_write_kreg_ctxt(dd, kr_rcvhdrtailaddr, ctxt,
			dd->rcd[ctxt]->rcvhdrqtailaddr_phys);
		qib_write_kreg_ctxt(dd, kr_rcvhdraddr, ctxt,
			dd->rcd[ctxt]->rcvhdrq_phys);

		if (ctxt == 0 && !dd->cspec->dummy_hdrq)
			alloc_dummy_hdrq(dd);
	}
	if (op & QIB_RCVCTRL_CTXT_DIS)
		dd->rcvctrl &= ~(mask << SYM_LSB(RcvCtrl, PortEnable));
	if (op & QIB_RCVCTRL_INTRAVAIL_ENB)
		dd->rcvctrl |= (mask << QLOGIC_IB_R_INTRAVAIL_SHIFT);
	if (op & QIB_RCVCTRL_INTRAVAIL_DIS)
		dd->rcvctrl &= ~(mask << QLOGIC_IB_R_INTRAVAIL_SHIFT);
	qib_write_kreg(dd, kr_rcvctrl, dd->rcvctrl);
	if ((op & QIB_RCVCTRL_INTRAVAIL_ENB) && dd->rhdrhead_intr_off) {
		/* arm rcv interrupt */
		val = qib_read_ureg32(dd, ur_rcvhdrhead, ctxt) |
			dd->rhdrhead_intr_off;
		qib_write_ureg(dd, ur_rcvhdrhead, val, ctxt);
	}
	if (op & QIB_RCVCTRL_CTXT_ENB) {
		/*
		 * Init the context registers also; if we were
		 * disabled, tail and head should both be zero
		 * already from the enable, but since we don't
		 * know, we have to do it explicitly.
		 */
		val = qib_read_ureg32(dd, ur_rcvegrindextail, ctxt);
		qib_write_ureg(dd, ur_rcvegrindexhead, val, ctxt);

		val = qib_read_ureg32(dd, ur_rcvhdrtail, ctxt);
		dd->rcd[ctxt]->head = val;
		/* If kctxt, interrupt on next receive. */
		if (ctxt < dd->first_user_ctxt)
			val |= dd->rhdrhead_intr_off;
		qib_write_ureg(dd, ur_rcvhdrhead, val, ctxt);
	}
	if (op & QIB_RCVCTRL_CTXT_DIS) {
		/*
		 * Be paranoid, and never write 0's to these, just use an
		 * unused page.  Of course,
		 * rcvhdraddr points to a large chunk of memory, so this
		 * could still trash things, but at least it won't trash
		 * page 0, and by disabling the ctxt, it should stop "soon",
		 * even if a packet or two is in already in flight after we
		 * disabled the ctxt.  Only 6120 has this issue.
		 */
		if (ctxt >= 0) {
			qib_write_kreg_ctxt(dd, kr_rcvhdrtailaddr, ctxt,
					    dd->cspec->dummy_hdrq_phys);
			qib_write_kreg_ctxt(dd, kr_rcvhdraddr, ctxt,
					    dd->cspec->dummy_hdrq_phys);
		} else {
			unsigned i;

			for (i = 0; i < dd->cfgctxts; i++) {
				qib_write_kreg_ctxt(dd, kr_rcvhdrtailaddr,
					    i, dd->cspec->dummy_hdrq_phys);
				qib_write_kreg_ctxt(dd, kr_rcvhdraddr,
					    i, dd->cspec->dummy_hdrq_phys);
			}
		}
	}
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);
}