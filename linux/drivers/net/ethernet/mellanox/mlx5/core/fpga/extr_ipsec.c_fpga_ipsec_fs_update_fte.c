#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_root_namespace {struct mlx5_core_dev* dev; } ;
struct mlx5_flow_group {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct mailbox_mod {int dummy; } ;
struct TYPE_3__ {int esp_id; int action; } ;
struct fs_fte {TYPE_1__ action; } ;
struct TYPE_4__ {int (* update_fte ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct mlx5_flow_group*,int,struct fs_fte*) ;} ;

/* Variables and functions */
 int MLX5_FLOW_CONTEXT_ACTION_DECRYPT ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCRYPT ; 
 int /*<<< orphan*/  egress_to_fs_ft (int) ; 
 TYPE_2__* mlx5_fs_cmd_get_default (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_spec_mailbox (struct mlx5_core_dev*,struct fs_fte*,struct mailbox_mod*) ; 
 int /*<<< orphan*/  restore_spec_mailbox (struct fs_fte*,struct mailbox_mod*) ; 

__attribute__((used)) static int fpga_ipsec_fs_update_fte(struct mlx5_flow_root_namespace *ns,
				    struct mlx5_flow_table *ft,
				    struct mlx5_flow_group *fg,
				    int modify_mask,
				    struct fs_fte *fte,
				    bool is_egress)
{
	int (*update_fte)(struct mlx5_flow_root_namespace *ns,
			  struct mlx5_flow_table *ft,
			  struct mlx5_flow_group *fg,
			  int modify_mask,
			  struct fs_fte *fte) =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(is_egress))->update_fte;
	struct mlx5_core_dev *dev = ns->dev;
	bool is_esp = fte->action.esp_id;
	struct mailbox_mod mbox_mod;
	int ret;

	if (!is_esp ||
	    !(fte->action.action &
	      (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
	       MLX5_FLOW_CONTEXT_ACTION_DECRYPT)))
		return update_fte(ns, ft, fg, modify_mask, fte);

	modify_spec_mailbox(dev, fte, &mbox_mod);
	ret = update_fte(ns, ft, fg, modify_mask, fte);
	restore_spec_mailbox(fte, &mbox_mod);

	return ret;
}