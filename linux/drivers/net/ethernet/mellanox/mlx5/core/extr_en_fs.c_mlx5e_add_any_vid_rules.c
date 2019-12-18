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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID ; 
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID ; 
 int mlx5e_add_vlan_rule (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_add_any_vid_rules(struct mlx5e_priv *priv)
{
	int err;

	err = mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID, 0);
	if (err)
		return err;

	return mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID, 0);
}