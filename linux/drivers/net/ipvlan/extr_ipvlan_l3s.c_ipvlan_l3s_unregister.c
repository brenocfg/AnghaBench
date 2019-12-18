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
struct net_device {int /*<<< orphan*/ * l3mdev_ops; int /*<<< orphan*/  priv_flags; } ;
struct ipvl_port {int /*<<< orphan*/  pnet; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  IFF_L3MDEV_RX_HANDLER ; 
 int /*<<< orphan*/  ipvlan_unregister_nf_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 

void ipvlan_l3s_unregister(struct ipvl_port *port)
{
	struct net_device *dev = port->dev;

	ASSERT_RTNL();

	dev->priv_flags &= ~IFF_L3MDEV_RX_HANDLER;
	ipvlan_unregister_nf_hook(read_pnet(&port->pnet));
	dev->l3mdev_ops = NULL;
}