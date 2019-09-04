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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  restart_queue2; } ;
struct igb_ring {int /*<<< orphan*/  tx_syncp2; TYPE_1__ tx_stats; int /*<<< orphan*/  queue_index; struct net_device* netdev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ const igb_desc_unused (struct igb_ring*) ; 
 int /*<<< orphan*/  netif_stop_subqueue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __igb_maybe_stop_tx(struct igb_ring *tx_ring, const u16 size)
{
	struct net_device *netdev = tx_ring->netdev;

	netif_stop_subqueue(netdev, tx_ring->queue_index);

	/* Herbert's original patch had:
	 *  smp_mb__after_netif_stop_queue();
	 * but since that doesn't exist yet, just open code it.
	 */
	smp_mb();

	/* We need to check again in a case another CPU has just
	 * made room available.
	 */
	if (igb_desc_unused(tx_ring) < size)
		return -EBUSY;

	/* A reprieve! */
	netif_wake_subqueue(netdev, tx_ring->queue_index);

	u64_stats_update_begin(&tx_ring->tx_syncp2);
	tx_ring->tx_stats.restart_queue2++;
	u64_stats_update_end(&tx_ring->tx_syncp2);

	return 0;
}