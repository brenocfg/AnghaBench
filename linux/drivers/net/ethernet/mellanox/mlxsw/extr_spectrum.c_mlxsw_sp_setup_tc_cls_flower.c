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
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct flow_cls_offload {int command; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_CLS_DESTROY 132 
#define  FLOW_CLS_REPLACE 131 
#define  FLOW_CLS_STATS 130 
#define  FLOW_CLS_TMPLT_CREATE 129 
#define  FLOW_CLS_TMPLT_DESTROY 128 
 struct mlxsw_sp* mlxsw_sp_acl_block_mlxsw_sp (struct mlxsw_sp_acl_block*) ; 
 int /*<<< orphan*/  mlxsw_sp_flower_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct flow_cls_offload*) ; 
 int mlxsw_sp_flower_replace (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct flow_cls_offload*) ; 
 int mlxsw_sp_flower_stats (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct flow_cls_offload*) ; 
 int mlxsw_sp_flower_tmplt_create (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  mlxsw_sp_flower_tmplt_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct flow_cls_offload*) ; 

__attribute__((used)) static int
mlxsw_sp_setup_tc_cls_flower(struct mlxsw_sp_acl_block *acl_block,
			     struct flow_cls_offload *f)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_acl_block_mlxsw_sp(acl_block);

	switch (f->command) {
	case FLOW_CLS_REPLACE:
		return mlxsw_sp_flower_replace(mlxsw_sp, acl_block, f);
	case FLOW_CLS_DESTROY:
		mlxsw_sp_flower_destroy(mlxsw_sp, acl_block, f);
		return 0;
	case FLOW_CLS_STATS:
		return mlxsw_sp_flower_stats(mlxsw_sp, acl_block, f);
	case FLOW_CLS_TMPLT_CREATE:
		return mlxsw_sp_flower_tmplt_create(mlxsw_sp, acl_block, f);
	case FLOW_CLS_TMPLT_DESTROY:
		mlxsw_sp_flower_tmplt_destroy(mlxsw_sp, acl_block, f);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}