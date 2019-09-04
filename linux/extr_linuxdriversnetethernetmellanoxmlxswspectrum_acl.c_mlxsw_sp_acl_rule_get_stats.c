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
typedef  void* u64 ;
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  counter_index; } ;
struct mlxsw_sp_acl_rule {void* last_packets; void* last_bytes; void* last_used; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_rule_info* mlxsw_sp_acl_rule_rulei (struct mlxsw_sp_acl_rule*) ; 
 int mlxsw_sp_flow_counter_get (struct mlxsw_sp*,int /*<<< orphan*/ ,void**,void**) ; 

int mlxsw_sp_acl_rule_get_stats(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_rule *rule,
				u64 *packets, u64 *bytes, u64 *last_use)

{
	struct mlxsw_sp_acl_rule_info *rulei;
	u64 current_packets;
	u64 current_bytes;
	int err;

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	err = mlxsw_sp_flow_counter_get(mlxsw_sp, rulei->counter_index,
					&current_packets, &current_bytes);
	if (err)
		return err;

	*packets = current_packets - rule->last_packets;
	*bytes = current_bytes - rule->last_bytes;
	*last_use = rule->last_used;

	rule->last_bytes = current_bytes;
	rule->last_packets = current_packets;

	return 0;
}