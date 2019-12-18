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
struct igc_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IGC_RESETTING ; 
 int /*<<< orphan*/  igc_down (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_all_rx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_all_tx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_irq (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_release_hw_control (struct igc_adapter*) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __igc_close(struct net_device *netdev, bool suspending)
{
	struct igc_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__IGC_RESETTING, &adapter->state));

	igc_down(adapter);

	igc_release_hw_control(adapter);

	igc_free_irq(adapter);

	igc_free_all_tx_resources(adapter);
	igc_free_all_rx_resources(adapter);

	return 0;
}