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
struct flow_block_offload {scalar_t__ binder_type; int command; int /*<<< orphan*/  block; int /*<<< orphan*/ * driver_block_list; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;
typedef  int /*<<< orphan*/  flow_setup_cb_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  FLOW_BLOCK_BIND 129 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS ; 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  FLOW_BLOCK_UNBIND 128 
 int /*<<< orphan*/  IS_ERR (struct flow_block_cb*) ; 
 int PTR_ERR (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_add (struct flow_block_cb*,struct flow_block_offload*) ; 
 struct flow_block_cb* flow_block_cb_alloc (int /*<<< orphan*/ *,struct mlxsw_sp_port*,struct mlxsw_sp_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_block_cb_free (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_is_busy (int /*<<< orphan*/ *,struct mlxsw_sp_port*,int /*<<< orphan*/ *) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_block_cb_list ; 
 int /*<<< orphan*/ * mlxsw_sp_setup_tc_block_cb_matchall_eg ; 
 int /*<<< orphan*/ * mlxsw_sp_setup_tc_block_cb_matchall_ig ; 
 int mlxsw_sp_setup_tc_block_flower_bind (struct mlxsw_sp_port*,struct flow_block_offload*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_setup_tc_block_flower_unbind (struct mlxsw_sp_port*,struct flow_block_offload*,int) ; 

__attribute__((used)) static int mlxsw_sp_setup_tc_block(struct mlxsw_sp_port *mlxsw_sp_port,
				   struct flow_block_offload *f)
{
	struct flow_block_cb *block_cb;
	flow_setup_cb_t *cb;
	bool ingress;
	int err;

	if (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS) {
		cb = mlxsw_sp_setup_tc_block_cb_matchall_ig;
		ingress = true;
	} else if (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS) {
		cb = mlxsw_sp_setup_tc_block_cb_matchall_eg;
		ingress = false;
	} else {
		return -EOPNOTSUPP;
	}

	f->driver_block_list = &mlxsw_sp_block_cb_list;

	switch (f->command) {
	case FLOW_BLOCK_BIND:
		if (flow_block_cb_is_busy(cb, mlxsw_sp_port,
					  &mlxsw_sp_block_cb_list))
			return -EBUSY;

		block_cb = flow_block_cb_alloc(cb, mlxsw_sp_port,
					       mlxsw_sp_port, NULL);
		if (IS_ERR(block_cb))
			return PTR_ERR(block_cb);
		err = mlxsw_sp_setup_tc_block_flower_bind(mlxsw_sp_port, f,
							  ingress);
		if (err) {
			flow_block_cb_free(block_cb);
			return err;
		}
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &mlxsw_sp_block_cb_list);
		return 0;
	case FLOW_BLOCK_UNBIND:
		mlxsw_sp_setup_tc_block_flower_unbind(mlxsw_sp_port,
						      f, ingress);
		block_cb = flow_block_cb_lookup(f->block, cb, mlxsw_sp_port);
		if (!block_cb)
			return -ENOENT;

		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}