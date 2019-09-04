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
struct ip_tunnel_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr4; } ;

/* Variables and functions */
 struct ip_tunnel_parm mlxsw_sp_ipip_netdev_parms4 (struct net_device const*) ; 
 TYPE_1__ mlxsw_sp_ipip_parms4_daddr (struct ip_tunnel_parm) ; 

__attribute__((used)) static __be32 mlxsw_sp_ipip_netdev_daddr4(const struct net_device *ol_dev)
{

	struct ip_tunnel_parm parms4 = mlxsw_sp_ipip_netdev_parms4(ol_dev);

	return mlxsw_sp_ipip_parms4_daddr(parms4).addr4;
}