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
struct qib_devdata {unsigned long long control; TYPE_1__* cspec; int /*<<< orphan*/  pport; } ;
struct TYPE_2__ {unsigned long long errormask; } ;

/* Variables and functions */
 unsigned long long E_SPKT_ERRS_IGNORE ; 
 int /*<<< orphan*/  kr_control ; 
 int /*<<< orphan*/  kr_errclear ; 
 int /*<<< orphan*/  kr_errmask ; 
 int /*<<< orphan*/  kr_hwerrclear ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  qib_6120_set_intr_state (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  qib_cancel_sends (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_force_pio_avail_update (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void qib_6120_clear_freeze(struct qib_devdata *dd)
{
	/* disable error interrupts, to avoid confusion */
	qib_write_kreg(dd, kr_errmask, 0ULL);

	/* also disable interrupts; errormask is sometimes overwritten */
	qib_6120_set_intr_state(dd, 0);

	qib_cancel_sends(dd->pport);

	/* clear the freeze, and be sure chip saw it */
	qib_write_kreg(dd, kr_control, dd->control);
	qib_read_kreg32(dd, kr_scratch);

	/* force in-memory update now we are out of freeze */
	qib_force_pio_avail_update(dd);

	/*
	 * force new interrupt if any hwerr, error or interrupt bits are
	 * still set, and clear "safe" send packet errors related to freeze
	 * and cancelling sends.  Re-enable error interrupts before possible
	 * force of re-interrupt on pending interrupts.
	 */
	qib_write_kreg(dd, kr_hwerrclear, 0ULL);
	qib_write_kreg(dd, kr_errclear, E_SPKT_ERRS_IGNORE);
	qib_write_kreg(dd, kr_errmask, dd->cspec->errormask);
	qib_6120_set_intr_state(dd, 1);
}