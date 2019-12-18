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
struct mlxsw_sp_ipip_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int __mlxsw_sp_ipip_entry_update_tunnel (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_netdevice_ipip_ul_down_event(struct mlxsw_sp *mlxsw_sp,
				      struct mlxsw_sp_ipip_entry *ipip_entry,
				      struct net_device *ul_dev)
{
	/* A down underlay device causes encapsulated packets to not be
	 * forwarded, but decap still works. So refresh next hops without
	 * touching anything else.
	 */
	return __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
						   false, false, true, NULL);
}