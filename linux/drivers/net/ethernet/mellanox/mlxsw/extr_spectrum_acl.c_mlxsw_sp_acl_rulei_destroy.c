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
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  act_block; scalar_t__ action_created; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_rule_info*) ; 
 int /*<<< orphan*/  mlxsw_afa_block_destroy (int /*<<< orphan*/ ) ; 

void mlxsw_sp_acl_rulei_destroy(struct mlxsw_sp_acl_rule_info *rulei)
{
	if (rulei->action_created)
		mlxsw_afa_block_destroy(rulei->act_block);
	kfree(rulei);
}