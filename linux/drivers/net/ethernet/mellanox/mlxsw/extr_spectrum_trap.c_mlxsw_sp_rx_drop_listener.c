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
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; struct mlxsw_sp_port** ports; } ;
struct devlink_port {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct mlxsw_sp* devlink_trap_ctx_priv (void*) ; 
 int /*<<< orphan*/  devlink_trap_report (struct devlink*,struct sk_buff*,void*,struct devlink_port*) ; 
 struct devlink_port* mlxsw_core_port_devlink_port_get (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ mlxsw_sp_rx_listener (struct mlxsw_sp*,struct sk_buff*,size_t,struct mlxsw_sp_port*) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_rx_drop_listener(struct sk_buff *skb, u8 local_port,
				      void *trap_ctx)
{
	struct devlink_port *in_devlink_port;
	struct mlxsw_sp_port *mlxsw_sp_port;
	struct mlxsw_sp *mlxsw_sp;
	struct devlink *devlink;

	mlxsw_sp = devlink_trap_ctx_priv(trap_ctx);
	mlxsw_sp_port = mlxsw_sp->ports[local_port];

	if (mlxsw_sp_rx_listener(mlxsw_sp, skb, local_port, mlxsw_sp_port))
		return;

	devlink = priv_to_devlink(mlxsw_sp->core);
	in_devlink_port = mlxsw_core_port_devlink_port_get(mlxsw_sp->core,
							   local_port);
	skb_push(skb, ETH_HLEN);
	devlink_trap_report(devlink, skb, trap_ctx, in_devlink_port);
	consume_skb(skb);
}