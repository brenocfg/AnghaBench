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
struct __ip6_tnl_parm {int dummy; } ;
struct ip6_tnl {struct __ip6_tnl_parm parms; } ;

/* Variables and functions */
 struct ip6_tnl* netdev_priv (struct net_device const*) ; 

struct __ip6_tnl_parm
mlxsw_sp_ipip_netdev_parms6(const struct net_device *ol_dev)
{
	struct ip6_tnl *tun = netdev_priv(ol_dev);

	return tun->parms;
}