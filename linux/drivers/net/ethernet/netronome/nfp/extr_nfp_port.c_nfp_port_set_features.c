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
struct nfp_port {scalar_t__ tc_offload_cnt; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int EBUSY ; 
 int NETIF_F_HW_TC ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

int nfp_port_set_features(struct net_device *netdev, netdev_features_t features)
{
	struct nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	if (!port)
		return 0;

	if ((netdev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC) &&
	    port->tc_offload_cnt) {
		netdev_err(netdev, "Cannot disable HW TC offload while offloads active\n");
		return -EBUSY;
	}

	return 0;
}