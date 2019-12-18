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
struct net_device {int dummy; } ;
struct kvaser_pciefd_can {int dummy; } ;

/* Variables and functions */
 int kvaser_pciefd_bus_on (struct kvaser_pciefd_can*) ; 
 struct kvaser_pciefd_can* netdev_priv (struct net_device*) ; 
 int open_candev (struct net_device*) ; 

__attribute__((used)) static int kvaser_pciefd_open(struct net_device *netdev)
{
	int err;
	struct kvaser_pciefd_can *can = netdev_priv(netdev);

	err = open_candev(netdev);
	if (err)
		return err;

	err = kvaser_pciefd_bus_on(can);
	if (err)
		return err;

	return 0;
}