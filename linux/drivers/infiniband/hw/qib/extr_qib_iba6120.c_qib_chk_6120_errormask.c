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
struct qib_devdata {int flags; TYPE_1__* cspec; int /*<<< orphan*/  pcidev; } ;
struct TYPE_2__ {unsigned long errormask; unsigned long hwerrmask; } ;

/* Variables and functions */
 int QIB_INITTED ; 
 int QLOGIC_IB_C_FREEZEMODE ; 
 int /*<<< orphan*/  kr_control ; 
 int /*<<< orphan*/  kr_errclear ; 
 int /*<<< orphan*/  kr_errmask ; 
 int /*<<< orphan*/  kr_hwerrclear ; 
 int /*<<< orphan*/  kr_hwerrstatus ; 
 int /*<<< orphan*/  kr_intclear ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int,unsigned long,unsigned long,int,unsigned long) ; 
 int qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 unsigned long qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void qib_chk_6120_errormask(struct qib_devdata *dd)
{
	static u32 fixed;
	u32 ctrl;
	unsigned long errormask;
	unsigned long hwerrs;

	if (!dd->cspec->errormask || !(dd->flags & QIB_INITTED))
		return;

	errormask = qib_read_kreg64(dd, kr_errmask);

	if (errormask == dd->cspec->errormask)
		return;
	fixed++;

	hwerrs = qib_read_kreg64(dd, kr_hwerrstatus);
	ctrl = qib_read_kreg32(dd, kr_control);

	qib_write_kreg(dd, kr_errmask,
		dd->cspec->errormask);

	if ((hwerrs & dd->cspec->hwerrmask) ||
	    (ctrl & QLOGIC_IB_C_FREEZEMODE)) {
		qib_write_kreg(dd, kr_hwerrclear, 0ULL);
		qib_write_kreg(dd, kr_errclear, 0ULL);
		/* force re-interrupt of pending events, just in case */
		qib_write_kreg(dd, kr_intclear, 0ULL);
		qib_devinfo(dd->pcidev,
			 "errormask fixed(%u) %lx->%lx, ctrl %x hwerr %lx\n",
			 fixed, errormask, (unsigned long)dd->cspec->errormask,
			 ctrl, hwerrs);
	}
}