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
struct mlxsw_sp_ipip_entry {struct net_device* ol_dev; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_entry_destroy (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_entry_ol_down_event (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*) ; 

void mlxsw_sp_ipip_entry_demote_tunnel(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_ipip_entry *ipip_entry)
{
	struct net_device *ol_dev = ipip_entry->ol_dev;

	if (ol_dev->flags & IFF_UP)
		mlxsw_sp_ipip_entry_ol_down_event(mlxsw_sp, ipip_entry);
	mlxsw_sp_ipip_entry_destroy(mlxsw_sp, ipip_entry);
}