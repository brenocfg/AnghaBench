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
struct nfp_repr {struct nfp_port* port; } ;
struct nfp_port {int dummy; } ;
struct nfp_net {struct nfp_port* port; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 void* netdev_priv (struct net_device*) ; 
 scalar_t__ nfp_netdev_is_nfp_net (struct net_device*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 

struct nfp_port *nfp_port_from_netdev(struct net_device *netdev)
{
	if (nfp_netdev_is_nfp_net(netdev)) {
		struct nfp_net *nn = netdev_priv(netdev);

		return nn->port;
	}

	if (nfp_netdev_is_nfp_repr(netdev)) {
		struct nfp_repr *repr = netdev_priv(netdev);

		return repr->port;
	}

	WARN(1, "Unknown netdev type for nfp_port\n");

	return NULL;
}