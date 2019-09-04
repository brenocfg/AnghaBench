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
typedef  int /*<<< orphan*/  tc_setup_cb_t ;
struct tc_block_offload {scalar_t__ binder_type; int command; int /*<<< orphan*/  block; int /*<<< orphan*/  extack; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ TCF_BLOCK_BINDER_TYPE_CLSACT_EGRESS ; 
 scalar_t__ TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  TC_BLOCK_BIND 129 
#define  TC_BLOCK_UNBIND 128 
 int /*<<< orphan*/ * mlxsw_sp_setup_tc_block_cb_matchall_eg ; 
 int /*<<< orphan*/ * mlxsw_sp_setup_tc_block_cb_matchall_ig ; 
 int mlxsw_sp_setup_tc_block_flower_bind (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_setup_tc_block_flower_unbind (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int tcf_block_cb_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sp_port*,struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_cb_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sp_port*) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc_block(struct mlxsw_sp_port *mlxsw_sp_port,
				   struct tc_block_offload *f)
{
	tc_setup_cb_t *cb;
	bool ingress;
	int err;

	if (f->binder_type == TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS) {
		cb = mlxsw_sp_setup_tc_block_cb_matchall_ig;
		ingress = true;
	} else if (f->binder_type == TCF_BLOCK_BINDER_TYPE_CLSACT_EGRESS) {
		cb = mlxsw_sp_setup_tc_block_cb_matchall_eg;
		ingress = false;
	} else {
		return -EOPNOTSUPP;
	}

	switch (f->command) {
	case TC_BLOCK_BIND:
		err = tcf_block_cb_register(f->block, cb, mlxsw_sp_port,
					    mlxsw_sp_port, f->extack);
		if (err)
			return err;
		err = mlxsw_sp_setup_tc_block_flower_bind(mlxsw_sp_port,
							  f->block, ingress,
							  f->extack);
		if (err) {
			tcf_block_cb_unregister(f->block, cb, mlxsw_sp_port);
			return err;
		}
		return 0;
	case TC_BLOCK_UNBIND:
		mlxsw_sp_setup_tc_block_flower_unbind(mlxsw_sp_port,
						      f->block, ingress);
		tcf_block_cb_unregister(f->block, cb, mlxsw_sp_port);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}