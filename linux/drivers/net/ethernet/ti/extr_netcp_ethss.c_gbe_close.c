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
struct netcp_intf {int dummy; } ;
struct net_device {int dummy; } ;
struct gbe_priv {int dummy; } ;
struct gbe_intf {TYPE_1__* slave; struct gbe_priv* gbe_dev; } ;
struct TYPE_2__ {int open; int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBE_RXHOOK_ORDER ; 
 int /*<<< orphan*/  GBE_TXHOOK_ORDER ; 
 int /*<<< orphan*/  NETCP_LINK_STATE_INVALID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbe_rxhook ; 
 int /*<<< orphan*/  gbe_slave_stop (struct gbe_intf*) ; 
 int /*<<< orphan*/  gbe_txhook ; 
 int /*<<< orphan*/  gbe_unregister_cpts (struct gbe_priv*) ; 
 int /*<<< orphan*/  netcp_unregister_rxhook (struct netcp_intf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gbe_intf*) ; 
 int /*<<< orphan*/  netcp_unregister_txhook (struct netcp_intf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gbe_intf*) ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gbe_close(void *intf_priv, struct net_device *ndev)
{
	struct gbe_intf *gbe_intf = intf_priv;
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct gbe_priv *gbe_dev = gbe_intf->gbe_dev;

	gbe_unregister_cpts(gbe_dev);

	gbe_slave_stop(gbe_intf);

	netcp_unregister_rxhook(netcp, GBE_RXHOOK_ORDER, gbe_rxhook, gbe_intf);
	netcp_unregister_txhook(netcp, GBE_TXHOOK_ORDER, gbe_txhook, gbe_intf);

	gbe_intf->slave->open = false;
	atomic_set(&gbe_intf->slave->link_state, NETCP_LINK_STATE_INVALID);
	return 0;
}