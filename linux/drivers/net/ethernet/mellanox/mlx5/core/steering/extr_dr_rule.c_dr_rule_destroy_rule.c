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
struct mlx5dr_rule {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; TYPE_2__* matcher; } ;
struct mlx5dr_domain {int type; } ;
struct TYPE_4__ {TYPE_1__* tbl; } ;
struct TYPE_3__ {struct mlx5dr_domain* dmn; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MLX5DR_DOMAIN_TYPE_FDB 130 
#define  MLX5DR_DOMAIN_TYPE_NIC_RX 129 
#define  MLX5DR_DOMAIN_TYPE_NIC_TX 128 
 int /*<<< orphan*/  dr_rule_destroy_rule_fdb (struct mlx5dr_rule*) ; 
 int /*<<< orphan*/  dr_rule_destroy_rule_nic (struct mlx5dr_rule*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dr_rule_remove_action_members (struct mlx5dr_rule*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_rule*) ; 

__attribute__((used)) static int dr_rule_destroy_rule(struct mlx5dr_rule *rule)
{
	struct mlx5dr_domain *dmn = rule->matcher->tbl->dmn;

	switch (dmn->type) {
	case MLX5DR_DOMAIN_TYPE_NIC_RX:
		dr_rule_destroy_rule_nic(rule, &rule->rx);
		break;
	case MLX5DR_DOMAIN_TYPE_NIC_TX:
		dr_rule_destroy_rule_nic(rule, &rule->tx);
		break;
	case MLX5DR_DOMAIN_TYPE_FDB:
		dr_rule_destroy_rule_fdb(rule);
		break;
	default:
		return -EINVAL;
	}

	dr_rule_remove_action_members(rule);
	kfree(rule);
	return 0;
}