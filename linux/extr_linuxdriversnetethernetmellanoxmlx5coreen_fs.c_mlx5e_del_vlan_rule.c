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
typedef  size_t u16 ;
struct TYPE_3__ {int /*<<< orphan*/ ** active_cvlans_rule; int /*<<< orphan*/ ** active_svlans_rule; int /*<<< orphan*/ * any_svlan_rule; int /*<<< orphan*/ * any_cvlan_rule; int /*<<< orphan*/ * untagged_rule; } ;
struct TYPE_4__ {TYPE_1__ vlan; } ;
struct mlx5e_priv {TYPE_2__ fs; } ;
typedef  enum mlx5e_vlan_rule_type { ____Placeholder_mlx5e_vlan_rule_type } mlx5e_vlan_rule_type ;

/* Variables and functions */
#define  MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID 132 
#define  MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID 131 
#define  MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID 130 
#define  MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID 129 
#define  MLX5E_VLAN_RULE_TYPE_UNTAGGED 128 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_vport_context_update_vlans (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_del_vlan_rule(struct mlx5e_priv *priv,
				enum mlx5e_vlan_rule_type rule_type, u16 vid)
{
	switch (rule_type) {
	case MLX5E_VLAN_RULE_TYPE_UNTAGGED:
		if (priv->fs.vlan.untagged_rule) {
			mlx5_del_flow_rules(priv->fs.vlan.untagged_rule);
			priv->fs.vlan.untagged_rule = NULL;
		}
		break;
	case MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID:
		if (priv->fs.vlan.any_cvlan_rule) {
			mlx5_del_flow_rules(priv->fs.vlan.any_cvlan_rule);
			priv->fs.vlan.any_cvlan_rule = NULL;
		}
		break;
	case MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID:
		if (priv->fs.vlan.any_svlan_rule) {
			mlx5_del_flow_rules(priv->fs.vlan.any_svlan_rule);
			priv->fs.vlan.any_svlan_rule = NULL;
		}
		break;
	case MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID:
		if (priv->fs.vlan.active_svlans_rule[vid]) {
			mlx5_del_flow_rules(priv->fs.vlan.active_svlans_rule[vid]);
			priv->fs.vlan.active_svlans_rule[vid] = NULL;
		}
		break;
	case MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID:
		if (priv->fs.vlan.active_cvlans_rule[vid]) {
			mlx5_del_flow_rules(priv->fs.vlan.active_cvlans_rule[vid]);
			priv->fs.vlan.active_cvlans_rule[vid] = NULL;
		}
		mlx5e_vport_context_update_vlans(priv);
		break;
	}
}