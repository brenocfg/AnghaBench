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
struct qib_devdata {int /*<<< orphan*/  (* f_free_irq ) (struct qib_devdata*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  (* f_set_intr_state ) (struct qib_devdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_BADINTR ; 
 int /*<<< orphan*/  QIB_INITTED ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qib_devdata*) ; 

void qib_bad_intrstatus(struct qib_devdata *dd)
{
	static int allbits;

	/* separate routine, for better optimization of qib_intr() */

	/*
	 * We print the message and disable interrupts, in hope of
	 * having a better chance of debugging the problem.
	 */
	qib_dev_err(dd,
		"Read of chip interrupt status failed disabling interrupts\n");
	if (allbits++) {
		/* disable interrupt delivery, something is very wrong */
		if (allbits == 2)
			dd->f_set_intr_state(dd, 0);
		if (allbits == 3) {
			qib_dev_err(dd,
				"2nd bad interrupt status, unregistering interrupts\n");
			dd->flags |= QIB_BADINTR;
			dd->flags &= ~QIB_INITTED;
			dd->f_free_irq(dd);
		}
	}
}