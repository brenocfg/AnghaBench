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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct ip_tunnel {TYPE_1__ parms; } ;

/* Variables and functions */
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device const*) ; 
 struct ip_tunnel* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static struct net_device *
__mlxsw_sp_ipip_netdev_ul_dev_get(const struct net_device *ol_dev)
{
	struct ip_tunnel *tun = netdev_priv(ol_dev);
	struct net *net = dev_net(ol_dev);

	return __dev_get_by_index(net, tun->parms.link);
}