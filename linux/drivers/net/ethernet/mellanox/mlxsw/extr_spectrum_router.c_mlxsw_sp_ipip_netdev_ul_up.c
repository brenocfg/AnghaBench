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
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 struct net_device* __mlxsw_sp_ipip_netdev_ul_dev_get (struct net_device*) ; 

__attribute__((used)) static bool mlxsw_sp_ipip_netdev_ul_up(struct net_device *ol_dev)
{
	struct net_device *ul_dev = __mlxsw_sp_ipip_netdev_ul_dev_get(ol_dev);

	return ul_dev ? (ul_dev->flags & IFF_UP) : true;
}