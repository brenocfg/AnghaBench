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
struct mlxsw_rx_listener {int dummy; } ;
struct mlxsw_rx_listener_item {int /*<<< orphan*/  list; void* priv; struct mlxsw_rx_listener rxl; } ;
struct mlxsw_core {int /*<<< orphan*/  rx_listener_list; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlxsw_rx_listener_item* __find_rx_listener_item (struct mlxsw_core*,struct mlxsw_rx_listener const*,void*) ; 
 struct mlxsw_rx_listener_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_core_rx_listener_register(struct mlxsw_core *mlxsw_core,
				    const struct mlxsw_rx_listener *rxl,
				    void *priv)
{
	struct mlxsw_rx_listener_item *rxl_item;

	rxl_item = __find_rx_listener_item(mlxsw_core, rxl, priv);
	if (rxl_item)
		return -EEXIST;
	rxl_item = kmalloc(sizeof(*rxl_item), GFP_KERNEL);
	if (!rxl_item)
		return -ENOMEM;
	rxl_item->rxl = *rxl;
	rxl_item->priv = priv;

	list_add_rcu(&rxl_item->list, &mlxsw_core->rx_listener_list);
	return 0;
}