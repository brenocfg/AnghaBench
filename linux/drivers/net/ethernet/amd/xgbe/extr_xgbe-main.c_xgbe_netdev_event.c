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
struct xgbe_prv_data {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ netdev_ops; } ;

/* Variables and functions */
#define  NETDEV_CHANGENAME 128 
 int NOTIFY_DONE ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xgbe_debugfs_rename (struct xgbe_prv_data*) ; 
 scalar_t__ xgbe_get_netdev_ops () ; 

__attribute__((used)) static int xgbe_netdev_event(struct notifier_block *nb, unsigned long event,
			     void *data)
{
	struct net_device *netdev = netdev_notifier_info_to_dev(data);
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	if (netdev->netdev_ops != xgbe_get_netdev_ops())
		goto out;

	switch (event) {
	case NETDEV_CHANGENAME:
		xgbe_debugfs_rename(pdata);
		break;

	default:
		break;
	}

out:
	return NOTIFY_DONE;
}