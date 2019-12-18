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
typedef  size_t u32 ;
struct ena_tx_buffer {int /*<<< orphan*/  skb; } ;
struct ena_ring {size_t ring_size; int /*<<< orphan*/  qid; int /*<<< orphan*/  netdev; struct ena_tx_buffer* tx_buffer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_unmap_tx_skb (struct ena_ring*,struct ena_tx_buffer*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_free_tx_bufs(struct ena_ring *tx_ring)
{
	bool print_once = true;
	u32 i;

	for (i = 0; i < tx_ring->ring_size; i++) {
		struct ena_tx_buffer *tx_info = &tx_ring->tx_buffer_info[i];

		if (!tx_info->skb)
			continue;

		if (print_once) {
			netdev_notice(tx_ring->netdev,
				      "free uncompleted tx skb qid %d idx 0x%x\n",
				      tx_ring->qid, i);
			print_once = false;
		} else {
			netdev_dbg(tx_ring->netdev,
				   "free uncompleted tx skb qid %d idx 0x%x\n",
				   tx_ring->qid, i);
		}

		ena_unmap_tx_skb(tx_ring, tx_info);

		dev_kfree_skb_any(tx_info->skb);
	}
	netdev_tx_reset_queue(netdev_get_tx_queue(tx_ring->netdev,
						  tx_ring->qid));
}