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
struct pedit_headers_action {int pedits; } ;
struct mlx5e_tc_flow_parse_attr {int max_mod_hdr_actions; int /*<<< orphan*/  mod_hdr_actions; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_UN_SZ_BYTES (int /*<<< orphan*/ ) ; 
 size_t TCA_PEDIT_KEY_EX_CMD_ADD ; 
 size_t TCA_PEDIT_KEY_EX_CMD_SET ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int mlx5e_flow_namespace_max_modify_action (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_action_in_add_action_in_auto ; 

__attribute__((used)) static int alloc_mod_hdr_actions(struct mlx5e_priv *priv,
				 struct pedit_headers_action *hdrs,
				 int namespace,
				 struct mlx5e_tc_flow_parse_attr *parse_attr)
{
	int nkeys, action_size, max_actions;

	nkeys = hdrs[TCA_PEDIT_KEY_EX_CMD_SET].pedits +
		hdrs[TCA_PEDIT_KEY_EX_CMD_ADD].pedits;
	action_size = MLX5_UN_SZ_BYTES(set_action_in_add_action_in_auto);

	max_actions = mlx5e_flow_namespace_max_modify_action(priv->mdev, namespace);
	/* can get up to crazingly 16 HW actions in 32 bits pedit SW key */
	max_actions = min(max_actions, nkeys * 16);

	parse_attr->mod_hdr_actions = kcalloc(max_actions, action_size, GFP_KERNEL);
	if (!parse_attr->mod_hdr_actions)
		return -ENOMEM;

	parse_attr->max_mod_hdr_actions = max_actions;
	return 0;
}