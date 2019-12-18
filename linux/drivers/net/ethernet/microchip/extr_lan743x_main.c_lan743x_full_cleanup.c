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
struct lan743x_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan743x_hardware_cleanup (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_mdiobus_cleanup (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_pci_cleanup (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan743x_full_cleanup(struct lan743x_adapter *adapter)
{
	unregister_netdev(adapter->netdev);

	lan743x_mdiobus_cleanup(adapter);
	lan743x_hardware_cleanup(adapter);
	lan743x_pci_cleanup(adapter);
}