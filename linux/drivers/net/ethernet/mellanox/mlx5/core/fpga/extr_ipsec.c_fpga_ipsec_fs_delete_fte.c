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
struct mlx5_fpga_ipsec_rule {int /*<<< orphan*/  ctx; } ;
struct mlx5_fpga_ipsec {int dummy; } ;
struct mlx5_fpga_device {struct mlx5_fpga_ipsec* ipsec; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_root_namespace {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;
struct mailbox_mod {int dummy; } ;
struct TYPE_3__ {int esp_id; int action; } ;
struct fs_fte {TYPE_1__ action; } ;
struct TYPE_4__ {int (* delete_fte ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,struct fs_fte*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int MLX5_FLOW_CONTEXT_ACTION_DECRYPT ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCRYPT ; 
 int /*<<< orphan*/  egress_to_fs_ft (int) ; 
 int /*<<< orphan*/  mlx5_fpga_ipsec_delete_sa_ctx (int /*<<< orphan*/ ) ; 
 TYPE_2__* mlx5_fs_cmd_get_default (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_spec_mailbox (struct mlx5_core_dev*,struct fs_fte*,struct mailbox_mod*) ; 
 int /*<<< orphan*/  restore_spec_mailbox (struct fs_fte*,struct mailbox_mod*) ; 
 int /*<<< orphan*/  rule_delete (struct mlx5_fpga_ipsec*,struct mlx5_fpga_ipsec_rule*) ; 
 struct mlx5_fpga_ipsec_rule* rule_search (struct mlx5_fpga_ipsec*,struct fs_fte*) ; 

__attribute__((used)) static int fpga_ipsec_fs_delete_fte(struct mlx5_flow_root_namespace *ns,
				    struct mlx5_flow_table *ft,
				    struct fs_fte *fte,
				    bool is_egress)
{
	int (*delete_fte)(struct mlx5_flow_root_namespace *ns,
			  struct mlx5_flow_table *ft,
			  struct fs_fte *fte) =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(is_egress))->delete_fte;
	struct mlx5_core_dev *dev = ns->dev;
	struct mlx5_fpga_device *fdev = dev->fpga;
	struct mlx5_fpga_ipsec *fipsec = fdev->ipsec;
	struct mlx5_fpga_ipsec_rule *rule;
	bool is_esp = fte->action.esp_id;
	struct mailbox_mod mbox_mod;
	int ret;

	if (!is_esp ||
	    !(fte->action.action &
	      (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
	       MLX5_FLOW_CONTEXT_ACTION_DECRYPT)))
		return delete_fte(ns, ft, fte);

	rule = rule_search(fipsec, fte);
	if (!rule)
		return -ENOENT;

	mlx5_fpga_ipsec_delete_sa_ctx(rule->ctx);
	rule_delete(fipsec, rule);

	modify_spec_mailbox(dev, fte, &mbox_mod);
	ret = delete_fte(ns, ft, fte);
	restore_spec_mailbox(fte, &mbox_mod);

	return ret;
}