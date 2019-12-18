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
struct net_device {int mtu; } ;
struct iavf_adapter {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  vsi; } ;

/* Variables and functions */
 scalar_t__ CLIENT_ENABLED (struct iavf_adapter*) ; 
 int /*<<< orphan*/  IAVF_FLAG_RESET_NEEDED ; 
 int /*<<< orphan*/  IAVF_FLAG_SERVICE_CLIENT_REQUESTED ; 
 int /*<<< orphan*/  iavf_notify_client_l2_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_wq ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iavf_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	netdev->mtu = new_mtu;
	if (CLIENT_ENABLED(adapter)) {
		iavf_notify_client_l2_params(&adapter->vsi);
		adapter->flags |= IAVF_FLAG_SERVICE_CLIENT_REQUESTED;
	}
	adapter->flags |= IAVF_FLAG_RESET_NEEDED;
	queue_work(iavf_wq, &adapter->reset_task);

	return 0;
}