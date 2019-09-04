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
typedef  int /*<<< orphan*/  u32 ;
struct qib_devdata {int flags; int /*<<< orphan*/ * int_counter; } ;
struct qib_ctxtdata {unsigned long long ctxt; struct qib_devdata* dd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int QIB_BADINTR ; 
 unsigned long long QIB_I_RCVAVAIL_LSB ; 
 unsigned long long QIB_I_RCVURG_LSB ; 
 int QIB_PRESENT ; 
 int /*<<< orphan*/  kr_intclear ; 
 int /*<<< orphan*/  qib_kreceive (struct qib_ctxtdata*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t qib_7322pintr(int irq, void *data)
{
	struct qib_ctxtdata *rcd = data;
	struct qib_devdata *dd = rcd->dd;
	u32 npkts;

	if ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)
		/*
		 * This return value is not great, but we do not want the
		 * interrupt core code to remove our interrupt handler
		 * because we don't appear to be handling an interrupt
		 * during a chip reset.
		 */
		return IRQ_HANDLED;

	this_cpu_inc(*dd->int_counter);

	/* Clear the interrupt bit we expect to be set. */
	qib_write_kreg(dd, kr_intclear, ((1ULL << QIB_I_RCVAVAIL_LSB) |
		       (1ULL << QIB_I_RCVURG_LSB)) << rcd->ctxt);

	qib_kreceive(rcd, NULL, &npkts);

	return IRQ_HANDLED;
}