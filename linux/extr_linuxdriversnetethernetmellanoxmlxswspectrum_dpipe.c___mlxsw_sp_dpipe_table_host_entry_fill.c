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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_rif {int dummy; } ;
struct devlink_dpipe_value {int mapping_valid; int /*<<< orphan*/ * value; int /*<<< orphan*/  value_size; int /*<<< orphan*/  mapping_value; } ;
struct devlink_dpipe_entry {struct devlink_dpipe_value* action_values; struct devlink_dpipe_value* match_values; } ;

/* Variables and functions */
 size_t MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP ; 
 size_t MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_dev_ifindex (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_index (struct mlxsw_sp_rif*) ; 

__attribute__((used)) static void
__mlxsw_sp_dpipe_table_host_entry_fill(struct devlink_dpipe_entry *entry,
				       struct mlxsw_sp_rif *rif,
				       unsigned char *ha, void *dip)
{
	struct devlink_dpipe_value *value;
	u32 *rif_value;
	u8 *ha_value;

	/* Set Match RIF index */
	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_RIF];

	rif_value = value->value;
	*rif_value = mlxsw_sp_rif_index(rif);
	value->mapping_value = mlxsw_sp_rif_dev_ifindex(rif);
	value->mapping_valid = true;

	/* Set Match DIP */
	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_HOST_MATCH_DIP];
	memcpy(value->value, dip, value->value_size);

	/* Set Action DMAC */
	value = entry->action_values;
	ha_value = value->value;
	ether_addr_copy(ha_value, ha);
}