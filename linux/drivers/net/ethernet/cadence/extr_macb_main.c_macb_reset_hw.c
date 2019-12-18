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
typedef  int u32 ;
struct macb_queue {int dummy; } ;
struct macb {unsigned int num_queues; int caps; struct macb_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRSTAT ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  ISR ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int MACB_CAPS_ISR_CLEAR_ON_WRITE ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  RE ; 
 int /*<<< orphan*/  RSR ; 
 int /*<<< orphan*/  TE ; 
 int /*<<< orphan*/  TSR ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_readl (struct macb_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_writel (struct macb_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void macb_reset_hw(struct macb *bp)
{
	struct macb_queue *queue;
	unsigned int q;
	u32 ctrl = macb_readl(bp, NCR);

	/* Disable RX and TX (XXX: Should we halt the transmission
	 * more gracefully?)
	 */
	ctrl &= ~(MACB_BIT(RE) | MACB_BIT(TE));

	/* Clear the stats registers (XXX: Update stats first?) */
	ctrl |= MACB_BIT(CLRSTAT);

	macb_writel(bp, NCR, ctrl);

	/* Clear all status flags */
	macb_writel(bp, TSR, -1);
	macb_writel(bp, RSR, -1);

	/* Disable all interrupts */
	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		queue_writel(queue, IDR, -1);
		queue_readl(queue, ISR);
		if (bp->caps & MACB_CAPS_ISR_CLEAR_ON_WRITE)
			queue_writel(queue, ISR, -1);
	}
}