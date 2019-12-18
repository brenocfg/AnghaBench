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
struct netcp_intf {int dummy; } ;
struct net_device {int dummy; } ;
struct gbe_intf {int /*<<< orphan*/  slave; int /*<<< orphan*/  gbe_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gbe_module ; 
 int /*<<< orphan*/  netcp_ethss_update_link_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 struct gbe_intf* netcp_module_get_intf_data (int /*<<< orphan*/ *,struct netcp_intf*) ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void gbe_adjust_link(struct net_device *ndev)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct gbe_intf *gbe_intf;

	gbe_intf = netcp_module_get_intf_data(&gbe_module, netcp);
	if (!gbe_intf)
		return;

	netcp_ethss_update_link_state(gbe_intf->gbe_dev, gbe_intf->slave,
				      ndev);
}