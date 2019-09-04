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
struct mlxsw_rx_listener {int /*<<< orphan*/  trap_id; int /*<<< orphan*/  local_port; int /*<<< orphan*/  func; } ;
struct mlxsw_event_listener {int /*<<< orphan*/  trap_id; } ;
struct mlxsw_event_listener_item {int /*<<< orphan*/  list; void* priv; struct mlxsw_event_listener el; } ;
struct mlxsw_core {int /*<<< orphan*/  event_listener_list; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_PORT_DONT_CARE ; 
 struct mlxsw_event_listener_item* __find_event_listener_item (struct mlxsw_core*,struct mlxsw_event_listener const*,void*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_event_listener_item*) ; 
 struct mlxsw_event_listener_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_event_listener_func ; 
 int mlxsw_core_rx_listener_register (struct mlxsw_core*,struct mlxsw_rx_listener const*,struct mlxsw_event_listener_item*) ; 

int mlxsw_core_event_listener_register(struct mlxsw_core *mlxsw_core,
				       const struct mlxsw_event_listener *el,
				       void *priv)
{
	int err;
	struct mlxsw_event_listener_item *el_item;
	const struct mlxsw_rx_listener rxl = {
		.func = mlxsw_core_event_listener_func,
		.local_port = MLXSW_PORT_DONT_CARE,
		.trap_id = el->trap_id,
	};

	el_item = __find_event_listener_item(mlxsw_core, el, priv);
	if (el_item)
		return -EEXIST;
	el_item = kmalloc(sizeof(*el_item), GFP_KERNEL);
	if (!el_item)
		return -ENOMEM;
	el_item->el = *el;
	el_item->priv = priv;

	err = mlxsw_core_rx_listener_register(mlxsw_core, &rxl, el_item);
	if (err)
		goto err_rx_listener_register;

	/* No reason to save item if we did not manage to register an RX
	 * listener for it.
	 */
	list_add_rcu(&el_item->list, &mlxsw_core->event_listener_list);

	return 0;

err_rx_listener_register:
	kfree(el_item);
	return err;
}