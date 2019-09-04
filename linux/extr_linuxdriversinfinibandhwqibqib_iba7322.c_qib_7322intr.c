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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qib_devdata {int flags; unsigned int first_user_ctxt; scalar_t__* rcd; int /*<<< orphan*/ * int_counter; TYPE_1__* cspec; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned long long main_int_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  Err ; 
 unsigned long long INT_MASK_P (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int QIB_BADINTR ; 
 int QIB_INITTED ; 
 unsigned long long QIB_I_BITSEXTANT ; 
 unsigned long long QIB_I_C_ERROR ; 
 unsigned long long QIB_I_GPIO ; 
 unsigned long long QIB_I_P_SDMAINT (int) ; 
 unsigned long long QIB_I_RCVAVAIL_LSB ; 
 unsigned long long QIB_I_RCVAVAIL_MASK ; 
 unsigned long long QIB_I_RCVURG_LSB ; 
 unsigned long long QIB_I_RCVURG_MASK ; 
 unsigned long long QIB_I_SPIOBUFAVAIL ; 
 int QIB_PRESENT ; 
 int /*<<< orphan*/  kr_intclear ; 
 int /*<<< orphan*/  kr_intstatus ; 
 int /*<<< orphan*/  qib_bad_intrstatus (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_handle_urcv (struct qib_devdata*,unsigned long long) ; 
 int /*<<< orphan*/  qib_ib_piobufavail (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_kreceive (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long long qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  sdma_7322_intr (struct qib_devdata*,unsigned long long) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned long long) ; 
 int /*<<< orphan*/  unlikely_7322_intr (struct qib_devdata*,unsigned long long) ; 

__attribute__((used)) static irqreturn_t qib_7322intr(int irq, void *data)
{
	struct qib_devdata *dd = data;
	irqreturn_t ret;
	u64 istat;
	u64 ctxtrbits;
	u64 rmask;
	unsigned i;
	u32 npkts;

	if ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT) {
		/*
		 * This return value is not great, but we do not want the
		 * interrupt core code to remove our interrupt handler
		 * because we don't appear to be handling an interrupt
		 * during a chip reset.
		 */
		ret = IRQ_HANDLED;
		goto bail;
	}

	istat = qib_read_kreg64(dd, kr_intstatus);

	if (unlikely(istat == ~0ULL)) {
		qib_bad_intrstatus(dd);
		qib_dev_err(dd, "Interrupt status all f's, skipping\n");
		/* don't know if it was our interrupt or not */
		ret = IRQ_NONE;
		goto bail;
	}

	istat &= dd->cspec->main_int_mask;
	if (unlikely(!istat)) {
		/* already handled, or shared and not us */
		ret = IRQ_NONE;
		goto bail;
	}

	this_cpu_inc(*dd->int_counter);

	/* handle "errors" of various kinds first, device ahead of port */
	if (unlikely(istat & (~QIB_I_BITSEXTANT | QIB_I_GPIO |
			      QIB_I_C_ERROR | INT_MASK_P(Err, 0) |
			      INT_MASK_P(Err, 1))))
		unlikely_7322_intr(dd, istat);

	/*
	 * Clear the interrupt bits we found set, relatively early, so we
	 * "know" know the chip will have seen this by the time we process
	 * the queue, and will re-interrupt if necessary.  The processor
	 * itself won't take the interrupt again until we return.
	 */
	qib_write_kreg(dd, kr_intclear, istat);

	/*
	 * Handle kernel receive queues before checking for pio buffers
	 * available since receives can overflow; piobuf waiters can afford
	 * a few extra cycles, since they were waiting anyway.
	 */
	ctxtrbits = istat & (QIB_I_RCVAVAIL_MASK | QIB_I_RCVURG_MASK);
	if (ctxtrbits) {
		rmask = (1ULL << QIB_I_RCVAVAIL_LSB) |
			(1ULL << QIB_I_RCVURG_LSB);
		for (i = 0; i < dd->first_user_ctxt; i++) {
			if (ctxtrbits & rmask) {
				ctxtrbits &= ~rmask;
				if (dd->rcd[i])
					qib_kreceive(dd->rcd[i], NULL, &npkts);
			}
			rmask <<= 1;
		}
		if (ctxtrbits) {
			ctxtrbits = (ctxtrbits >> QIB_I_RCVAVAIL_LSB) |
				(ctxtrbits >> QIB_I_RCVURG_LSB);
			qib_handle_urcv(dd, ctxtrbits);
		}
	}

	if (istat & (QIB_I_P_SDMAINT(0) | QIB_I_P_SDMAINT(1)))
		sdma_7322_intr(dd, istat);

	if ((istat & QIB_I_SPIOBUFAVAIL) && (dd->flags & QIB_INITTED))
		qib_ib_piobufavail(dd);

	ret = IRQ_HANDLED;
bail:
	return ret;
}