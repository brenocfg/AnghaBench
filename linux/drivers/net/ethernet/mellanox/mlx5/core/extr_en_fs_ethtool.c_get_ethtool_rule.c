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
struct mlx5e_ethtool_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5e_ethtool_rule* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_rule_to_list (struct mlx5e_priv*,struct mlx5e_ethtool_rule*) ; 
 int /*<<< orphan*/  del_ethtool_rule (struct mlx5e_priv*,struct mlx5e_ethtool_rule*) ; 
 struct mlx5e_ethtool_rule* find_ethtool_rule (struct mlx5e_priv*,int) ; 
 struct mlx5e_ethtool_rule* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5e_ethtool_rule *get_ethtool_rule(struct mlx5e_priv *priv,
						   int location)
{
	struct mlx5e_ethtool_rule *eth_rule;

	eth_rule = find_ethtool_rule(priv, location);
	if (eth_rule)
		del_ethtool_rule(priv, eth_rule);

	eth_rule = kzalloc(sizeof(*eth_rule), GFP_KERNEL);
	if (!eth_rule)
		return ERR_PTR(-ENOMEM);

	add_rule_to_list(priv, eth_rule);
	return eth_rule;
}