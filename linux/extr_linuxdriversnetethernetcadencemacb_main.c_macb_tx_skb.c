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
struct macb_tx_skb {int dummy; } ;
struct macb_queue {int /*<<< orphan*/  bp; struct macb_tx_skb* tx_skb; } ;

/* Variables and functions */
 size_t macb_tx_ring_wrap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct macb_tx_skb *macb_tx_skb(struct macb_queue *queue,
				       unsigned int index)
{
	return &queue->tx_skb[macb_tx_ring_wrap(queue->bp, index)];
}