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
struct mlxsw_event_listener_item {int /*<<< orphan*/  list; } ;
struct mlxsw_event_listener {int /*<<< orphan*/  trap_id; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_DONT_CARE ; 
 struct mlxsw_event_listener_item* __find_event_listener_item (struct mlxsw_core*,struct mlxsw_event_listener const*,void*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_event_listener_item*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_event_listener_func ; 
 int /*<<< orphan*/  mlxsw_core_rx_listener_unregister (struct mlxsw_core*,struct mlxsw_rx_listener const*,struct mlxsw_event_listener_item*) ; 

void mlxsw_core_event_listener_unregister(struct mlxsw_core *mlxsw_core,
					  const struct mlxsw_event_listener *el,
					  void *priv)
{
	struct mlxsw_event_listener_item *el_item;
	const struct mlxsw_rx_listener rxl = {
		.func = mlxsw_core_event_listener_func,
		.local_port = MLXSW_PORT_DONT_CARE,
		.trap_id = el->trap_id,
	};

	el_item = __find_event_listener_item(mlxsw_core, el, priv);
	if (!el_item)
		return;
	mlxsw_core_rx_listener_unregister(mlxsw_core, &rxl, el_item);
	list_del(&el_item->list);
	kfree(el_item);
}