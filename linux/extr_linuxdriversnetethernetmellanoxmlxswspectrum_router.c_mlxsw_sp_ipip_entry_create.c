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
struct mlxsw_sp_ipip_entry {int /*<<< orphan*/  ipip_list_node; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_2__ {int /*<<< orphan*/  ipip_list; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_ipip_entry* mlxsw_sp_ipip_entry_alloc (struct mlxsw_sp*,int,struct net_device*) ; 

__attribute__((used)) static struct mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_create(struct mlxsw_sp *mlxsw_sp,
			   enum mlxsw_sp_ipip_type ipipt,
			   struct net_device *ol_dev)
{
	struct mlxsw_sp_ipip_entry *ipip_entry;

	ipip_entry = mlxsw_sp_ipip_entry_alloc(mlxsw_sp, ipipt, ol_dev);
	if (IS_ERR(ipip_entry))
		return ipip_entry;

	list_add_tail(&ipip_entry->ipip_list_node,
		      &mlxsw_sp->router->ipip_list);

	return ipip_entry;
}