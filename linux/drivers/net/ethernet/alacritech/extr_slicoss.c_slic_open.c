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
struct slic_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct slic_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int slic_init_iface (struct slic_device*) ; 

__attribute__((used)) static int slic_open(struct net_device *dev)
{
	struct slic_device *sdev = netdev_priv(dev);
	int err;

	netif_carrier_off(dev);

	err = slic_init_iface(sdev);
	if (err) {
		netdev_err(dev, "failed to initialize interface: %i\n", err);
		return err;
	}

	netif_start_queue(dev);

	return 0;
}