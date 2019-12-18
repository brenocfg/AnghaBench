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
struct mlx5dr_rule_rx_tx {int dummy; } ;
struct mlx5dr_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dr_rule_clean_rule_members (struct mlx5dr_rule*,struct mlx5dr_rule_rx_tx*) ; 

__attribute__((used)) static int dr_rule_destroy_rule_nic(struct mlx5dr_rule *rule,
				    struct mlx5dr_rule_rx_tx *nic_rule)
{
	dr_rule_clean_rule_members(rule, nic_rule);
	return 0;
}