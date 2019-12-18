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
struct port {int /*<<< orphan*/  mem_res; int /*<<< orphan*/  npe; int /*<<< orphan*/  id; } ;
struct platform_device {int dummy; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 size_t NPE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ ** npe_port_tab ; 
 int /*<<< orphan*/  npe_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int eth_remove_one(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct phy_device *phydev = dev->phydev;
	struct port *port = netdev_priv(dev);

	unregister_netdev(dev);
	phy_disconnect(phydev);
	npe_port_tab[NPE_ID(port->id)] = NULL;
	npe_release(port->npe);
	release_resource(port->mem_res);
	free_netdev(dev);
	return 0;
}