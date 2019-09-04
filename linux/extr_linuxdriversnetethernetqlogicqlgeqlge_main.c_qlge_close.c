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
struct ql_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  QL_EEH_FATAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql_adapter_down (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_release_adapter_resources (struct ql_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlge_close(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	/* If we hit pci_channel_io_perm_failure
	 * failure condition, then we already
	 * brought the adapter down.
	 */
	if (test_bit(QL_EEH_FATAL, &qdev->flags)) {
		netif_err(qdev, drv, qdev->ndev, "EEH fatal did unload.\n");
		clear_bit(QL_EEH_FATAL, &qdev->flags);
		return 0;
	}

	/*
	 * Wait for device to recover from a reset.
	 * (Rarely happens, but possible.)
	 */
	while (!test_bit(QL_ADAPTER_UP, &qdev->flags))
		msleep(1);
	ql_adapter_down(qdev);
	ql_release_adapter_resources(qdev);
	return 0;
}