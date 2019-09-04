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
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  mpi_port_cfg_work; int /*<<< orphan*/  workqueue; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int /*<<< orphan*/  ifup ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int ql_change_rx_buffers (struct ql_adapter*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qlge_change_mtu(struct net_device *ndev, int new_mtu)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	int status;

	if (ndev->mtu == 1500 && new_mtu == 9000) {
		netif_err(qdev, ifup, qdev->ndev, "Changing to jumbo MTU.\n");
	} else if (ndev->mtu == 9000 && new_mtu == 1500) {
		netif_err(qdev, ifup, qdev->ndev, "Changing to normal MTU.\n");
	} else
		return -EINVAL;

	queue_delayed_work(qdev->workqueue,
			&qdev->mpi_port_cfg_work, 3*HZ);

	ndev->mtu = new_mtu;

	if (!netif_running(qdev->ndev)) {
		return 0;
	}

	status = ql_change_rx_buffers(qdev);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Changing MTU failed.\n");
	}

	return status;
}