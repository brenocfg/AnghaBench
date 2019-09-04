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
struct mlxsw_rx_listener_item {int /*<<< orphan*/  list; } ;
struct mlxsw_rx_listener {int dummy; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 struct mlxsw_rx_listener_item* __find_rx_listener_item (struct mlxsw_core*,struct mlxsw_rx_listener const*,void*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_rx_listener_item*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void mlxsw_core_rx_listener_unregister(struct mlxsw_core *mlxsw_core,
				       const struct mlxsw_rx_listener *rxl,
				       void *priv)
{
	struct mlxsw_rx_listener_item *rxl_item;

	rxl_item = __find_rx_listener_item(mlxsw_core, rxl, priv);
	if (!rxl_item)
		return;
	list_del_rcu(&rxl_item->list);
	synchronize_rcu();
	kfree(rxl_item);
}