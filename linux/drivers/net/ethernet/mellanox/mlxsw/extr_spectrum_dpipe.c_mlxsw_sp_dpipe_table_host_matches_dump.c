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
struct sk_buff {int dummy; } ;
struct devlink_dpipe_match {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; void* type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  DEVLINK_DPIPE_FIELD_IPV4_DST_IP ; 
 int /*<<< orphan*/  DEVLINK_DPIPE_FIELD_IPV6_DST_IP ; 
 void* DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devlink_dpipe_header_ipv4 ; 
 int /*<<< orphan*/  devlink_dpipe_header_ipv6 ; 
 int devlink_dpipe_match_put (struct sk_buff*,struct devlink_dpipe_match*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_header_metadata ; 

__attribute__((used)) static int mlxsw_sp_dpipe_table_host_matches_dump(struct sk_buff *skb, int type)
{
	struct devlink_dpipe_match match = {0};
	int err;

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	err = devlink_dpipe_match_put(skb, &match);
	if (err)
		return err;

	switch (type) {
	case AF_INET:
		match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
		match.header = &devlink_dpipe_header_ipv4;
		match.field_id = DEVLINK_DPIPE_FIELD_IPV4_DST_IP;
		break;
	case AF_INET6:
		match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
		match.header = &devlink_dpipe_header_ipv6;
		match.field_id = DEVLINK_DPIPE_FIELD_IPV6_DST_IP;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	return devlink_dpipe_match_put(skb, &match);
}