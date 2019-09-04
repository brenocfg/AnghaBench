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
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_acl_block_binding {int ingress; int /*<<< orphan*/  list; struct mlxsw_sp_port* mlxsw_sp_port; } ;
struct mlxsw_sp_acl_block {int /*<<< orphan*/  binding_list; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_block_binding*) ; 
 struct mlxsw_sp_acl_block_binding* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_lookup (struct mlxsw_sp_acl_block*,struct mlxsw_sp_port*,int) ; 
 int mlxsw_sp_acl_ruleset_bind (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_acl_block_binding*) ; 
 scalar_t__ mlxsw_sp_acl_ruleset_block_bound (struct mlxsw_sp_acl_block*) ; 

int mlxsw_sp_acl_block_bind(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_block *block,
			    struct mlxsw_sp_port *mlxsw_sp_port,
			    bool ingress)
{
	struct mlxsw_sp_acl_block_binding *binding;
	int err;

	if (WARN_ON(mlxsw_sp_acl_block_lookup(block, mlxsw_sp_port, ingress)))
		return -EEXIST;

	binding = kzalloc(sizeof(*binding), GFP_KERNEL);
	if (!binding)
		return -ENOMEM;
	binding->mlxsw_sp_port = mlxsw_sp_port;
	binding->ingress = ingress;

	if (mlxsw_sp_acl_ruleset_block_bound(block)) {
		err = mlxsw_sp_acl_ruleset_bind(mlxsw_sp, block, binding);
		if (err)
			goto err_ruleset_bind;
	}

	list_add(&binding->list, &block->binding_list);
	return 0;

err_ruleset_bind:
	kfree(binding);
	return err;
}