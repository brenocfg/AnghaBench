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
typedef  int /*<<< orphan*/  u32 ;
typedef  struct net_device const net_device ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 struct net_device const* __mlxsw_sp_ipip_netdev_ul_dev_get (struct net_device const*) ; 
 scalar_t__ l3mdev_fib_table (struct net_device const*) ; 

u32 mlxsw_sp_ipip_dev_ul_tb_id(const struct net_device *ol_dev)
{
	struct net_device *d = __mlxsw_sp_ipip_netdev_ul_dev_get(ol_dev);

	if (d)
		return l3mdev_fib_table(d) ? : RT_TABLE_MAIN;
	else
		return l3mdev_fib_table(ol_dev) ? : RT_TABLE_MAIN;
}