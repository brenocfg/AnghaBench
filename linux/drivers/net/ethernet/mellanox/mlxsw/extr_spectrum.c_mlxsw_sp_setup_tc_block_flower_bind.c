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
struct mlxsw_sp_port {struct mlxsw_sp_acl_block* eg_acl_block; struct mlxsw_sp_acl_block* ing_acl_block; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct flow_block_offload {int /*<<< orphan*/  extack; int /*<<< orphan*/  net; int /*<<< orphan*/  block; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct flow_block_cb*) ; 
 int PTR_ERR (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_add (struct flow_block_cb*,struct flow_block_offload*) ; 
 struct flow_block_cb* flow_block_cb_alloc (int /*<<< orphan*/ ,struct mlxsw_sp*,struct mlxsw_sp_acl_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_block_cb_decref (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_free (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_incref (struct flow_block_cb*) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp*) ; 
 struct mlxsw_sp_acl_block* flow_block_cb_priv (struct flow_block_cb*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_block_bind (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_port*,int,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_block* mlxsw_sp_acl_block_create (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_destroy (struct mlxsw_sp_acl_block*) ; 
 int /*<<< orphan*/  mlxsw_sp_block_cb_list ; 
 int /*<<< orphan*/  mlxsw_sp_setup_tc_block_cb_flower ; 
 int /*<<< orphan*/  mlxsw_sp_tc_block_flower_release ; 

__attribute__((used)) static int
mlxsw_sp_setup_tc_block_flower_bind(struct mlxsw_sp_port *mlxsw_sp_port,
			            struct flow_block_offload *f, bool ingress)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_acl_block *acl_block;
	struct flow_block_cb *block_cb;
	bool register_block = false;
	int err;

	block_cb = flow_block_cb_lookup(f->block,
					mlxsw_sp_setup_tc_block_cb_flower,
					mlxsw_sp);
	if (!block_cb) {
		acl_block = mlxsw_sp_acl_block_create(mlxsw_sp, f->net);
		if (!acl_block)
			return -ENOMEM;
		block_cb = flow_block_cb_alloc(mlxsw_sp_setup_tc_block_cb_flower,
					       mlxsw_sp, acl_block,
					       mlxsw_sp_tc_block_flower_release);
		if (IS_ERR(block_cb)) {
			mlxsw_sp_acl_block_destroy(acl_block);
			err = PTR_ERR(block_cb);
			goto err_cb_register;
		}
		register_block = true;
	} else {
		acl_block = flow_block_cb_priv(block_cb);
	}
	flow_block_cb_incref(block_cb);
	err = mlxsw_sp_acl_block_bind(mlxsw_sp, acl_block,
				      mlxsw_sp_port, ingress, f->extack);
	if (err)
		goto err_block_bind;

	if (ingress)
		mlxsw_sp_port->ing_acl_block = acl_block;
	else
		mlxsw_sp_port->eg_acl_block = acl_block;

	if (register_block) {
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &mlxsw_sp_block_cb_list);
	}

	return 0;

err_block_bind:
	if (!flow_block_cb_decref(block_cb))
		flow_block_cb_free(block_cb);
err_cb_register:
	return err;
}