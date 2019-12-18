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
struct ixgbe_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_RESET_REQUESTED ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ixgbe_ring_tx_pending (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_vf_tx_pending (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_watchdog_flush_tx(struct ixgbe_adapter *adapter)
{
	if (!netif_carrier_ok(adapter->netdev)) {
		if (ixgbe_ring_tx_pending(adapter) ||
		    ixgbe_vf_tx_pending(adapter)) {
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get done, so reset controller to flush Tx.
			 * (Do the reset outside of interrupt context).
			 */
			e_warn(drv, "initiating reset to clear Tx work after link loss\n");
			set_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
		}
	}
}