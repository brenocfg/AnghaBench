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
struct tc_action {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int max_mod_hdr_actions; int /*<<< orphan*/  mod_hdr_actions; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_CAP_ESW_FLOWTABLE_FDB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE_NIC_RX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_NAMESPACE_FDB ; 
 int MLX5_UN_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_modify_header_actions ; 
 int min (int,int) ; 
 int /*<<< orphan*/  set_action_in_add_action_in_auto ; 
 int tcf_pedit_nkeys (struct tc_action const*) ; 

__attribute__((used)) static int alloc_mod_hdr_actions(struct mlx5e_priv *priv,
				 const struct tc_action *a, int namespace,
				 struct mlx5e_tc_flow_parse_attr *parse_attr)
{
	int nkeys, action_size, max_actions;

	nkeys = tcf_pedit_nkeys(a);
	action_size = MLX5_UN_SZ_BYTES(set_action_in_add_action_in_auto);

	if (namespace == MLX5_FLOW_NAMESPACE_FDB) /* FDB offloading */
		max_actions = MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev, max_modify_header_actions);
	else /* namespace is MLX5_FLOW_NAMESPACE_KERNEL - NIC offloading */
		max_actions = MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, max_modify_header_actions);

	/* can get up to crazingly 16 HW actions in 32 bits pedit SW key */
	max_actions = min(max_actions, nkeys * 16);

	parse_attr->mod_hdr_actions = kcalloc(max_actions, action_size, GFP_KERNEL);
	if (!parse_attr->mod_hdr_actions)
		return -ENOMEM;

	parse_attr->max_mod_hdr_actions = max_actions;
	return 0;
}