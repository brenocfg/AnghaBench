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
struct TYPE_2__ {int /*<<< orphan*/  rx_listener; int /*<<< orphan*/  event_listener; } ;
struct mlxsw_listener {TYPE_1__ u; scalar_t__ is_event; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_core_event_listener_unregister (struct mlxsw_core*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mlxsw_core_rx_listener_unregister (struct mlxsw_core*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void mlxsw_core_listener_unregister(struct mlxsw_core *mlxsw_core,
				      const struct mlxsw_listener *listener,
				      void *priv)
{
	if (listener->is_event)
		mlxsw_core_event_listener_unregister(mlxsw_core,
						     &listener->u.event_listener,
						     priv);
	else
		mlxsw_core_rx_listener_unregister(mlxsw_core,
						  &listener->u.rx_listener,
						  priv);
}