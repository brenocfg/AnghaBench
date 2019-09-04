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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_mid {struct mlxsw_sp_mid* ports_in_mid; int /*<<< orphan*/  list; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 scalar_t__ bitmap_empty (struct mlxsw_sp_mid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,struct mlxsw_sp_mid*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mid*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_mc_remove_mdb_entry (struct mlxsw_sp*,struct mlxsw_sp_mid*) ; 

__attribute__((used)) static int mlxsw_sp_port_remove_from_mid(struct mlxsw_sp_port *mlxsw_sp_port,
					 struct mlxsw_sp_mid *mid)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	int err = 0;

	clear_bit(mlxsw_sp_port->local_port, mid->ports_in_mid);
	if (bitmap_empty(mid->ports_in_mid,
			 mlxsw_core_max_ports(mlxsw_sp->core))) {
		err = mlxsw_sp_mc_remove_mdb_entry(mlxsw_sp, mid);
		list_del(&mid->list);
		kfree(mid->ports_in_mid);
		kfree(mid);
	}
	return err;
}