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
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  hw_enc_features; int /*<<< orphan*/ * xfrmdev_ops; } ;
struct cxgb4_lld_info {int nports; struct net_device** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_HW_ESP ; 
 int /*<<< orphan*/  chcr_xfrmdev_ops ; 
 int /*<<< orphan*/  netdev_change_features (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void chcr_add_xfrmops(const struct cxgb4_lld_info *lld)
{
	struct net_device *netdev = NULL;
	int i;

	for (i = 0; i < lld->nports; i++) {
		netdev = lld->ports[i];
		if (!netdev)
			continue;
		netdev->xfrmdev_ops = &chcr_xfrmdev_ops;
		netdev->hw_enc_features |= NETIF_F_HW_ESP;
		netdev->features |= NETIF_F_HW_ESP;
		rtnl_lock();
		netdev_change_features(netdev);
		rtnl_unlock();
	}
}