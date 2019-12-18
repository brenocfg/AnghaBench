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
typedef  int u64 ;
struct qib_devdata {unsigned int pioavregs; int* pioavailkernel; int* pioavailshadow; int /*<<< orphan*/  pioavail_lock; int /*<<< orphan*/ * pioavailregs_dma; } ;

/* Variables and functions */
 int QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void update_send_bufs(struct qib_devdata *dd)
{
	unsigned long flags;
	unsigned i;
	const unsigned piobregs = dd->pioavregs;

	/*
	 * If the generation (check) bits have changed, then we update the
	 * busy bit for the corresponding PIO buffer.  This algorithm will
	 * modify positions to the value they already have in some cases
	 * (i.e., no change), but it's faster than changing only the bits
	 * that have changed.
	 *
	 * We would like to do this atomicly, to avoid spinlocks in the
	 * critical send path, but that's not really possible, given the
	 * type of changes, and that this routine could be called on
	 * multiple cpu's simultaneously, so we lock in this routine only,
	 * to avoid conflicting updates; all we change is the shadow, and
	 * it's a single 64 bit memory location, so by definition the update
	 * is atomic in terms of what other cpu's can see in testing the
	 * bits.  The spin_lock overhead isn't too bad, since it only
	 * happens when all buffers are in use, so only cpu overhead, not
	 * latency or bandwidth is affected.
	 */
	if (!dd->pioavailregs_dma)
		return;
	spin_lock_irqsave(&dd->pioavail_lock, flags);
	for (i = 0; i < piobregs; i++) {
		u64 pchbusy, pchg, piov, pnew;

		piov = le64_to_cpu(dd->pioavailregs_dma[i]);
		pchg = dd->pioavailkernel[i] &
			~(dd->pioavailshadow[i] ^ piov);
		pchbusy = pchg << QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT;
		if (pchg && (pchbusy & dd->pioavailshadow[i])) {
			pnew = dd->pioavailshadow[i] & ~pchbusy;
			pnew |= piov & pchbusy;
			dd->pioavailshadow[i] = pnew;
		}
	}
	spin_unlock_irqrestore(&dd->pioavail_lock, flags);
}