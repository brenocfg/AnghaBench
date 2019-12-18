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
struct mlxsw_sp_port {int /*<<< orphan*/ * eg_acl_block; int /*<<< orphan*/ * ing_acl_block; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct flow_block_offload {int /*<<< orphan*/  block; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_block_cb_decref (struct flow_block_cb*) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp*) ; 
 struct mlxsw_sp_acl_block* flow_block_cb_priv (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_block_unbind (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_setup_tc_block_cb_flower ; 

__attribute__((used)) static void
mlxsw_sp_setup_tc_block_flower_unbind(struct mlxsw_sp_port *mlxsw_sp_port,
				      struct flow_block_offload *f, bool ingress)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_acl_block *acl_block;
	struct flow_block_cb *block_cb;
	int err;

	block_cb = flow_block_cb_lookup(f->block,
					mlxsw_sp_setup_tc_block_cb_flower,
					mlxsw_sp);
	if (!block_cb)
		return;

	if (ingress)
		mlxsw_sp_port->ing_acl_block = NULL;
	else
		mlxsw_sp_port->eg_acl_block = NULL;

	acl_block = flow_block_cb_priv(block_cb);
	err = mlxsw_sp_acl_block_unbind(mlxsw_sp, acl_block,
					mlxsw_sp_port, ingress);
	if (!err && !flow_block_cb_decref(block_cb)) {
		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
	}
}