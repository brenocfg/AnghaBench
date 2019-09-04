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
struct ixgbe_adapter {int /*<<< orphan*/  test_rx_ring; int /*<<< orphan*/  test_tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_disable_rx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_disable_tx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_free_rx_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_free_tx_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_reset (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_free_desc_rings(struct ixgbe_adapter *adapter)
{
	/* Shut down the DMA engines now so they can be reinitialized later,
	 * since the test rings and normally used rings should overlap on
	 * queue 0 we can just use the standard disable Rx/Tx calls and they
	 * will take care of disabling the test rings for us.
	 */

	/* first Rx */
	ixgbe_disable_rx(adapter);

	/* now Tx */
	ixgbe_disable_tx(adapter);

	ixgbe_reset(adapter);

	ixgbe_free_tx_resources(&adapter->test_tx_ring);
	ixgbe_free_rx_resources(&adapter->test_rx_ring);
}