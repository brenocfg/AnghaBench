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
struct e1000_ring {struct e1000_adapter* adapter; } ;
struct e1000_adapter {int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int e1000_desc_unused (struct e1000_ring*) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static int __e1000_maybe_stop_tx(struct e1000_ring *tx_ring, int size)
{
	struct e1000_adapter *adapter = tx_ring->adapter;

	netif_stop_queue(adapter->netdev);
	/* Herbert's original patch had:
	 *  smp_mb__after_netif_stop_queue();
	 * but since that doesn't exist yet, just open code it.
	 */
	smp_mb();

	/* We need to check again in a case another CPU has just
	 * made room available.
	 */
	if (e1000_desc_unused(tx_ring) < size)
		return -EBUSY;

	/* A reprieve! */
	netif_start_queue(adapter->netdev);
	++adapter->restart_queue;
	return 0;
}