#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct devlink_dpipe_entry {int counter_valid; int /*<<< orphan*/  counter; void* index; TYPE_2__* action_values; TYPE_1__* match_values; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {int* value; int mapping_valid; int /*<<< orphan*/  mapping_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_RIF_COUNTER_EGRESS ; 
 int mlxsw_sp_rif_counter_value_get (struct mlxsw_sp*,struct mlxsw_sp_rif*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_dev_ifindex (struct mlxsw_sp_rif*) ; 
 void* mlxsw_sp_rif_index (struct mlxsw_sp_rif*) ; 

__attribute__((used)) static int mlxsw_sp_erif_entry_get(struct mlxsw_sp *mlxsw_sp,
				   struct devlink_dpipe_entry *entry,
				   struct mlxsw_sp_rif *rif,
				   bool counters_enabled)
{
	u32 *action_value;
	u32 *rif_value;
	u64 cnt;
	int err;

	/* Set Match RIF index */
	rif_value = entry->match_values->value;
	*rif_value = mlxsw_sp_rif_index(rif);
	entry->match_values->mapping_value = mlxsw_sp_rif_dev_ifindex(rif);
	entry->match_values->mapping_valid = true;

	/* Set Action Forwarding */
	action_value = entry->action_values->value;
	*action_value = 1;

	entry->counter_valid = false;
	entry->counter = 0;
	entry->index = mlxsw_sp_rif_index(rif);

	if (!counters_enabled)
		return 0;

	err = mlxsw_sp_rif_counter_value_get(mlxsw_sp, rif,
					     MLXSW_SP_RIF_COUNTER_EGRESS,
					     &cnt);
	if (!err) {
		entry->counter = cnt;
		entry->counter_valid = true;
	}
	return 0;
}