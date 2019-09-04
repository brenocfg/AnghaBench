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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct in6_addr {int dummy; } ;
struct devlink_dpipe_value {int value_size; void* value; struct devlink_dpipe_action* action; struct devlink_dpipe_match* match; } ;
struct devlink_dpipe_match {int dummy; } ;
struct devlink_dpipe_entry {int action_values_count; struct devlink_dpipe_value* action_values; int /*<<< orphan*/  match_values_count; struct devlink_dpipe_value* match_values; } ;
struct devlink_dpipe_action {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT ; 
 size_t MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP ; 
 size_t MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_dpipe_table_host_entry_prepare(struct devlink_dpipe_entry *entry,
					struct devlink_dpipe_value *match_values,
					struct devlink_dpipe_match *matches,
					struct devlink_dpipe_value *action_value,
					struct devlink_dpipe_action *action,
					int type)
{
	struct devlink_dpipe_value *match_value;
	struct devlink_dpipe_match *match;

	entry->match_values = match_values;
	entry->match_values_count = MLXSW_SP_DPIPE_TABLE_HOST_MATCH_COUNT;

	entry->action_values = action_value;
	entry->action_values_count = 1;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];

	match_value->match = match;
	match_value->value_size = sizeof(u32);
	match_value->value = kmalloc(match_value->value_size, GFP_KERNEL);
	if (!match_value->value)
		return -ENOMEM;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];
	match_value = &match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];

	match_value->match = match;
	switch (type) {
	case AF_INET:
		match_value->value_size = sizeof(u32);
		break;
	case AF_INET6:
		match_value->value_size = sizeof(struct in6_addr);
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	match_value->value = kmalloc(match_value->value_size, GFP_KERNEL);
	if (!match_value->value)
		return -ENOMEM;

	action_value->action = action;
	action_value->value_size = sizeof(u64);
	action_value->value = kmalloc(action_value->value_size, GFP_KERNEL);
	if (!action_value->value)
		return -ENOMEM;

	return 0;
}