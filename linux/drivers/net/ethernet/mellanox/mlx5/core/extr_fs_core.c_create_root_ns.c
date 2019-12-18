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
struct mlx5_flow_steering {int /*<<< orphan*/  dev; } ;
struct mlx5_flow_namespace {int /*<<< orphan*/  node; } ;
struct mlx5_flow_root_namespace {int table_type; int /*<<< orphan*/  chain_lock; struct mlx5_flow_namespace ns; int /*<<< orphan*/  underlay_qpns; struct mlx5_flow_cmds const* cmds; int /*<<< orphan*/  dev; } ;
struct mlx5_flow_cmds {int dummy; } ;
typedef  enum fs_flow_table_type { ____Placeholder_fs_flow_table_type } fs_flow_table_type ;

/* Variables and functions */
 int FS_FT_NIC_RX ; 
 int FS_FT_NIC_TX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MLX5_ACCEL_IPSEC_CAP_DEVICE ; 
 int /*<<< orphan*/  fs_init_namespace (struct mlx5_flow_namespace*) ; 
 struct mlx5_flow_root_namespace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_accel_ipsec_device_caps (int /*<<< orphan*/ ) ; 
 struct mlx5_flow_cmds* mlx5_fs_cmd_get_default (int) ; 
 struct mlx5_flow_cmds* mlx5_fs_cmd_get_default_ipsec_fpga_cmds (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_add_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_init_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_root_namespace
*create_root_ns(struct mlx5_flow_steering *steering,
		enum fs_flow_table_type table_type)
{
	const struct mlx5_flow_cmds *cmds = mlx5_fs_cmd_get_default(table_type);
	struct mlx5_flow_root_namespace *root_ns;
	struct mlx5_flow_namespace *ns;

	if (mlx5_accel_ipsec_device_caps(steering->dev) & MLX5_ACCEL_IPSEC_CAP_DEVICE &&
	    (table_type == FS_FT_NIC_RX || table_type == FS_FT_NIC_TX))
		cmds = mlx5_fs_cmd_get_default_ipsec_fpga_cmds(table_type);

	/* Create the root namespace */
	root_ns = kzalloc(sizeof(*root_ns), GFP_KERNEL);
	if (!root_ns)
		return NULL;

	root_ns->dev = steering->dev;
	root_ns->table_type = table_type;
	root_ns->cmds = cmds;

	INIT_LIST_HEAD(&root_ns->underlay_qpns);

	ns = &root_ns->ns;
	fs_init_namespace(ns);
	mutex_init(&root_ns->chain_lock);
	tree_init_node(&ns->node, NULL, NULL);
	tree_add_node(&ns->node, NULL);

	return root_ns;
}