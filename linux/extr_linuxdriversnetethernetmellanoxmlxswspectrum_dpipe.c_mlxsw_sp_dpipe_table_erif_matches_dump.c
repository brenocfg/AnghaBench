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
struct devlink_dpipe_match {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT ; 
 int /*<<< orphan*/  MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT ; 
 int devlink_dpipe_match_put (struct sk_buff*,struct devlink_dpipe_match*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_header_metadata ; 

__attribute__((used)) static int mlxsw_sp_dpipe_table_erif_matches_dump(void *priv,
						  struct sk_buff *skb)
{
	struct devlink_dpipe_match match = {0};

	match.type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match.header = &mlxsw_sp_dpipe_header_metadata;
	match.field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;

	return devlink_dpipe_match_put(skb, &match);
}