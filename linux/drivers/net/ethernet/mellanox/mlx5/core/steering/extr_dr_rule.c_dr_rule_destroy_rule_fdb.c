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
struct mlx5dr_rule {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dr_rule_destroy_rule_nic (struct mlx5dr_rule*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_rule_destroy_rule_fdb(struct mlx5dr_rule *rule)
{
	dr_rule_destroy_rule_nic(rule, &rule->rx);
	dr_rule_destroy_rule_nic(rule, &rule->tx);
	return 0;
}