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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;
struct net_device {int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  link ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int netif_running (struct net_device*) ; 
 int ql_adapter_down (struct ql_adapter*) ; 
 int ql_adapter_up (struct ql_adapter*) ; 

__attribute__((used)) static int qlge_update_hw_vlan_features(struct net_device *ndev,
					netdev_features_t features)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	int status = 0;
	bool need_restart = netif_running(ndev);

	if (need_restart) {
		status = ql_adapter_down(qdev);
		if (status) {
			netif_err(qdev, link, qdev->ndev,
				  "Failed to bring down the adapter\n");
			return status;
		}
	}

	/* update the features with resent change */
	ndev->features = features;

	if (need_restart) {
		status = ql_adapter_up(qdev);
		if (status) {
			netif_err(qdev, link, qdev->ndev,
				  "Failed to bring up the adapter\n");
			return status;
		}
	}

	return status;
}