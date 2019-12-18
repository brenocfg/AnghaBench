#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_fecparam {int dummy; } ;
struct efx_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; } ;
struct TYPE_2__ {int (* set_fecparam ) (struct efx_nic*,struct ethtool_fecparam*) ;int /*<<< orphan*/  get_fecparam; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*,struct ethtool_fecparam*) ; 

__attribute__((used)) static int efx_ethtool_set_fecparam(struct net_device *net_dev,
				    struct ethtool_fecparam *fecparam)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	int rc;

	if (!efx->phy_op || !efx->phy_op->get_fecparam)
		return -EOPNOTSUPP;
	mutex_lock(&efx->mac_lock);
	rc = efx->phy_op->set_fecparam(efx, fecparam);
	mutex_unlock(&efx->mac_lock);

	return rc;
}