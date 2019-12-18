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
struct igbvf_adapter {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IGBVF_RESETTING ; 
 int /*<<< orphan*/  igbvf_down (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_free_irq (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_free_rx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_free_tx_resources (int /*<<< orphan*/ ) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igbvf_close(struct net_device *netdev)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__IGBVF_RESETTING, &adapter->state));
	igbvf_down(adapter);

	igbvf_free_irq(adapter);

	igbvf_free_tx_resources(adapter->tx_ring);
	igbvf_free_rx_resources(adapter->rx_ring);

	return 0;
}