#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_fc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_flows; } ;
struct mlx5_eswitch {TYPE_1__ offloads; int /*<<< orphan*/  dev; } ;
struct mlx5_esw_flow_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_del_flow_rules (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  mlx5_fc_destroy (int /*<<< orphan*/ ,struct mlx5_fc*) ; 
 struct mlx5_fc* mlx5_flow_rule_counter (struct mlx5_flow_handle*) ; 

void
mlx5_eswitch_del_offloaded_rule(struct mlx5_eswitch *esw,
				struct mlx5_flow_handle *rule,
				struct mlx5_esw_flow_attr *attr)
{
	struct mlx5_fc *counter = NULL;

	counter = mlx5_flow_rule_counter(rule);
	mlx5_del_flow_rules(rule);
	mlx5_fc_destroy(esw->dev, counter);
	esw->offloads.num_flows--;
}