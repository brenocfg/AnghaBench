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
struct net_device {int dummy; } ;
struct igbvf_adapter {int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int EBUSY ; 
 int igbvf_desc_unused (int /*<<< orphan*/ ) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static int igbvf_maybe_stop_tx(struct net_device *netdev, int size)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);

	/* there is enough descriptors then we don't need to worry  */
	if (igbvf_desc_unused(adapter->tx_ring) >= size)
		return 0;

	netif_stop_queue(netdev);

	/* Herbert's original patch had:
	 *  smp_mb__after_netif_stop_queue();
	 * but since that doesn't exist yet, just open code it.
	 */
	smp_mb();

	/* We need to check again just in case room has been made available */
	if (igbvf_desc_unused(adapter->tx_ring) < size)
		return -EBUSY;

	netif_wake_queue(netdev);

	++adapter->restart_queue;
	return 0;
}