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
struct macb_queue {unsigned int tx_head; unsigned int tx_tail; struct macb* bp; } ;
struct macb {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISR ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int MACB_CAPS_ISR_CLEAR_ON_WRITE ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  TSTART ; 
 int /*<<< orphan*/  TXUBR ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_writel (struct macb_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void macb_tx_restart(struct macb_queue *queue)
{
	unsigned int head = queue->tx_head;
	unsigned int tail = queue->tx_tail;
	struct macb *bp = queue->bp;

	if (bp->caps & MACB_CAPS_ISR_CLEAR_ON_WRITE)
		queue_writel(queue, ISR, MACB_BIT(TXUBR));

	if (head == tail)
		return;

	macb_writel(bp, NCR, macb_readl(bp, NCR) | MACB_BIT(TSTART));
}