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
struct tcf_block_cb {int dummy; } ;
struct tcf_block {int /*<<< orphan*/  net; } ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp_acl_block* eg_acl_block; struct mlxsw_sp_acl_block* ing_acl_block; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct tcf_block_cb*) ; 
 int PTR_ERR (struct tcf_block_cb*) ; 
 struct tcf_block_cb* __tcf_block_cb_register (struct tcf_block*,int /*<<< orphan*/ ,struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  __tcf_block_cb_unregister (struct tcf_block*,struct tcf_block_cb*) ; 
 int mlxsw_sp_acl_block_bind (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_port*,int) ; 
 struct mlxsw_sp_acl_block* mlxsw_sp_acl_block_create (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_destroy (struct mlxsw_sp_acl_block*) ; 
 int /*<<< orphan*/  mlxsw_sp_setup_tc_block_cb_flower ; 
 int /*<<< orphan*/  tcf_block_cb_decref (struct tcf_block_cb*) ; 
 int /*<<< orphan*/  tcf_block_cb_incref (struct tcf_block_cb*) ; 
 struct tcf_block_cb* tcf_block_cb_lookup (struct tcf_block*,int /*<<< orphan*/ ,struct mlxsw_sp*) ; 
 struct mlxsw_sp_acl_block* tcf_block_cb_priv (struct tcf_block_cb*) ; 

__attribute__((used)) static int
mlxsw_sp_setup_tc_block_flower_bind(struct mlxsw_sp_port *mlxsw_sp_port,
				    struct tcf_block *block, bool ingress,
				    struct netlink_ext_ack *extack)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_acl_block *acl_block;
	struct tcf_block_cb *block_cb;
	int err;

	block_cb = tcf_block_cb_lookup(block, mlxsw_sp_setup_tc_block_cb_flower,
				       mlxsw_sp);
	if (!block_cb) {
		acl_block = mlxsw_sp_acl_block_create(mlxsw_sp, block->net);
		if (!acl_block)
			return -ENOMEM;
		block_cb = __tcf_block_cb_register(block,
						   mlxsw_sp_setup_tc_block_cb_flower,
						   mlxsw_sp, acl_block, extack);
		if (IS_ERR(block_cb)) {
			err = PTR_ERR(block_cb);
			goto err_cb_register;
		}
	} else {
		acl_block = tcf_block_cb_priv(block_cb);
	}
	tcf_block_cb_incref(block_cb);
	err = mlxsw_sp_acl_block_bind(mlxsw_sp, acl_block,
				      mlxsw_sp_port, ingress);
	if (err)
		goto err_block_bind;

	if (ingress)
		mlxsw_sp_port->ing_acl_block = acl_block;
	else
		mlxsw_sp_port->eg_acl_block = acl_block;

	return 0;

err_block_bind:
	if (!tcf_block_cb_decref(block_cb)) {
		__tcf_block_cb_unregister(block, block_cb);
err_cb_register:
		mlxsw_sp_acl_block_destroy(acl_block);
	}
	return err;
}