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
struct rocker_port {int dummy; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int rocker_cmd_set_port_settings_mtu (struct rocker_port*,int) ; 
 int rocker_port_open (struct net_device*) ; 
 int /*<<< orphan*/  rocker_port_stop (struct net_device*) ; 

__attribute__((used)) static int rocker_port_change_mtu(struct net_device *dev, int new_mtu)
{
	struct rocker_port *rocker_port = netdev_priv(dev);
	int running = netif_running(dev);
	int err;

	if (running)
		rocker_port_stop(dev);

	netdev_info(dev, "MTU change from %d to %d\n", dev->mtu, new_mtu);
	dev->mtu = new_mtu;

	err = rocker_cmd_set_port_settings_mtu(rocker_port, new_mtu);
	if (err)
		return err;

	if (running)
		err = rocker_port_open(dev);

	return err;
}