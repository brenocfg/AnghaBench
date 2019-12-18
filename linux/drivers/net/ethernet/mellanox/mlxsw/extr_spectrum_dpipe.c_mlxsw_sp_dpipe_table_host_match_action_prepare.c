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
struct devlink_dpipe_match {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; void* type; } ;
struct devlink_dpipe_action {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY ; 
 int /*<<< orphan*/  DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC ; 
 int /*<<< orphan*/  DEVLINK_DPIPE_FIELD_IPV4_DST_IP ; 
 int /*<<< orphan*/  DEVLINK_DPIPE_FIELD_IPV6_DST_IP ; 
 void* DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT ; 
 int /*<<< orphan*/  MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT ; 
 size_t MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP ; 
 size_t MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devlink_dpipe_header_ethernet ; 
 int /*<<< orphan*/  devlink_dpipe_header_ipv4 ; 
 int /*<<< orphan*/  devlink_dpipe_header_ipv6 ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_header_metadata ; 

__attribute__((used)) static void
mlxsw_sp_dpipe_table_host_match_action_prepare(struct devlink_dpipe_match *matches,
					       struct devlink_dpipe_action *action,
					       int type)
{
	struct devlink_dpipe_match *match;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	match = &matches[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];
	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	switch (type) {
	case AF_INET:
		match->header = &devlink_dpipe_header_ipv4;
		match->field_id = DEVLINK_DPIPE_FIELD_IPV4_DST_IP;
		break;
	case AF_INET6:
		match->header = &devlink_dpipe_header_ipv6;
		match->field_id = DEVLINK_DPIPE_FIELD_IPV6_DST_IP;
		break;
	default:
		WARN_ON(1);
		return;
	}

	action->type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action->header = &devlink_dpipe_header_ethernet;
	action->field_id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC;
}