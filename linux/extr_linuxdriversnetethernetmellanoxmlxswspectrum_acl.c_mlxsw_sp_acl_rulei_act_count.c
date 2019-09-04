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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  counter_index; int /*<<< orphan*/  act_block; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_afa_block_append_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 

int mlxsw_sp_acl_rulei_act_count(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_rule_info *rulei,
				 struct netlink_ext_ack *extack)
{
	return mlxsw_afa_block_append_counter(rulei->act_block,
					      &rulei->counter_index, extack);
}