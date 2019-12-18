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
struct ixgbevf_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbevf_configure_dcb (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_configure_rx (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_configure_tx (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_ipsec_restore (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_restore_vlan (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_set_rx_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_configure(struct ixgbevf_adapter *adapter)
{
	ixgbevf_configure_dcb(adapter);

	ixgbevf_set_rx_mode(adapter->netdev);

	ixgbevf_restore_vlan(adapter);
	ixgbevf_ipsec_restore(adapter);

	ixgbevf_configure_tx(adapter);
	ixgbevf_configure_rx(adapter);
}