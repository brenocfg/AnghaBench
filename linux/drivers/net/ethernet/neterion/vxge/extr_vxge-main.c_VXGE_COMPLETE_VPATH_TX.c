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
struct vxge_fifo {int /*<<< orphan*/  txq; int /*<<< orphan*/  handle; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int NR_SKB_COMPLETED ; 
 scalar_t__ __netif_tx_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_poll_tx (int /*<<< orphan*/ ,struct sk_buff***,int,int*) ; 

__attribute__((used)) static inline void VXGE_COMPLETE_VPATH_TX(struct vxge_fifo *fifo)
{
	struct sk_buff **skb_ptr = NULL;
	struct sk_buff **temp;
#define NR_SKB_COMPLETED 128
	struct sk_buff *completed[NR_SKB_COMPLETED];
	int more;

	do {
		more = 0;
		skb_ptr = completed;

		if (__netif_tx_trylock(fifo->txq)) {
			vxge_hw_vpath_poll_tx(fifo->handle, &skb_ptr,
						NR_SKB_COMPLETED, &more);
			__netif_tx_unlock(fifo->txq);
		}

		/* free SKBs */
		for (temp = completed; temp != skb_ptr; temp++)
			dev_consume_skb_irq(*temp);
	} while (more);
}