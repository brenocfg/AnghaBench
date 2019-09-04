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
struct devlink_dpipe_match {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; int /*<<< orphan*/  type; } ;
struct devlink_dpipe_action {int /*<<< orphan*/  field_id; int /*<<< orphan*/ * header; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY ; 
 int /*<<< orphan*/  DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT ; 
 int /*<<< orphan*/  MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT ; 
 int /*<<< orphan*/  MLXSW_SP_DPIPE_FIELD_METADATA_L3_FORWARD ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_header_metadata ; 

__attribute__((used)) static void
mlxsw_sp_erif_match_action_prepare(struct devlink_dpipe_match *match,
				   struct devlink_dpipe_action *action)
{
	action->type = DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY;
	action->header = &mlxsw_sp_dpipe_header_metadata;
	action->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_L3_FORWARD;

	match->type = DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT;
	match->header = &mlxsw_sp_dpipe_header_metadata;
	match->field_id = MLXSW_SP_DPIPE_FIELD_METADATA_ERIF_PORT;
}