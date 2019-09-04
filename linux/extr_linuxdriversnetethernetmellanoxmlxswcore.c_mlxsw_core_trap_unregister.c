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
struct mlxsw_listener {int /*<<< orphan*/  is_ctrl; int /*<<< orphan*/  trap_group; int /*<<< orphan*/  trap_id; int /*<<< orphan*/  unreg_action; int /*<<< orphan*/  is_event; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_HPKT_LEN ; 
 int /*<<< orphan*/  hpkt ; 
 int /*<<< orphan*/  mlxsw_core_listener_unregister (struct mlxsw_core*,struct mlxsw_listener const*,void*) ; 
 int /*<<< orphan*/  mlxsw_reg_hpkt_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_write (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 

void mlxsw_core_trap_unregister(struct mlxsw_core *mlxsw_core,
				const struct mlxsw_listener *listener,
				void *priv)
{
	char hpkt_pl[MLXSW_REG_HPKT_LEN];

	if (!listener->is_event) {
		mlxsw_reg_hpkt_pack(hpkt_pl, listener->unreg_action,
				    listener->trap_id, listener->trap_group,
				    listener->is_ctrl);
		mlxsw_reg_write(mlxsw_core, MLXSW_REG(hpkt), hpkt_pl);
	}

	mlxsw_core_listener_unregister(mlxsw_core, listener, priv);
}