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
struct TYPE_3__ {int /*<<< orphan*/  tot_num_rules; } ;
struct TYPE_4__ {TYPE_1__ ethtool; } ;
struct mlx5e_priv {TYPE_2__ fs; } ;
struct mlx5e_ethtool_rule {int /*<<< orphan*/  eth_ft; int /*<<< orphan*/  list; scalar_t__ rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5e_ethtool_rule*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (scalar_t__) ; 
 int /*<<< orphan*/  put_flow_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_ethtool_rule(struct mlx5e_priv *priv,
			     struct mlx5e_ethtool_rule *eth_rule)
{
	if (eth_rule->rule)
		mlx5_del_flow_rules(eth_rule->rule);
	list_del(&eth_rule->list);
	priv->fs.ethtool.tot_num_rules--;
	put_flow_table(eth_rule->eth_ft);
	kfree(eth_rule);
}