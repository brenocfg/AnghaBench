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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct xive_q {int /*<<< orphan*/  count; int /*<<< orphan*/  pending_count; } ;
struct xive_cpu {int pending_prio; size_t cppr; struct xive_q* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_VERBOSE (char*,size_t) ; 
 scalar_t__ TM_CPPR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ffs (int) ; 
 int /*<<< orphan*/  out_8 (scalar_t__,size_t) ; 
 scalar_t__ xive_read_eq (struct xive_q*,int) ; 
 scalar_t__ xive_tima ; 
 scalar_t__ xive_tima_offset ; 

__attribute__((used)) static u32 xive_scan_interrupts(struct xive_cpu *xc, bool just_peek)
{
	u32 irq = 0;
	u8 prio;

	/* Find highest pending priority */
	while (xc->pending_prio != 0) {
		struct xive_q *q;

		prio = ffs(xc->pending_prio) - 1;
		DBG_VERBOSE("scan_irq: trying prio %d\n", prio);

		/* Try to fetch */
		irq = xive_read_eq(&xc->queue[prio], just_peek);

		/* Found something ? That's it */
		if (irq)
			break;

		/* Clear pending bits */
		xc->pending_prio &= ~(1 << prio);

		/*
		 * Check if the queue count needs adjusting due to
		 * interrupts being moved away. See description of
		 * xive_dec_target_count()
		 */
		q = &xc->queue[prio];
		if (atomic_read(&q->pending_count)) {
			int p = atomic_xchg(&q->pending_count, 0);
			if (p) {
				WARN_ON(p > atomic_read(&q->count));
				atomic_sub(p, &q->count);
			}
		}
	}

	/* If nothing was found, set CPPR to 0xff */
	if (irq == 0)
		prio = 0xff;

	/* Update HW CPPR to match if necessary */
	if (prio != xc->cppr) {
		DBG_VERBOSE("scan_irq: adjusting CPPR to %d\n", prio);
		xc->cppr = prio;
		out_8(xive_tima + xive_tima_offset + TM_CPPR, prio);
	}

	return irq;
}