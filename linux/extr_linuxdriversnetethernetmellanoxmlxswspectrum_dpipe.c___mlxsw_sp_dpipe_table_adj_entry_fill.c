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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_rif {int dummy; } ;
struct devlink_dpipe_value {int mapping_valid; int /*<<< orphan*/  mapping_value; int /*<<< orphan*/ * value; } ;
struct devlink_dpipe_entry {struct devlink_dpipe_value* action_values; struct devlink_dpipe_value* match_values; } ;

/* Variables and functions */
 size_t MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC ; 
 size_t MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT ; 
 size_t MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX ; 
 size_t MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX ; 
 size_t MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_dev_ifindex (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_index (struct mlxsw_sp_rif*) ; 

__attribute__((used)) static void
__mlxsw_sp_dpipe_table_adj_entry_fill(struct devlink_dpipe_entry *entry,
				      u32 adj_index, u32 adj_size,
				      u32 adj_hash_index, unsigned char *ha,
				      struct mlxsw_sp_rif *rif)
{
	struct devlink_dpipe_value *value;
	u32 *p_rif_value;
	u32 *p_index;

	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_INDEX];
	p_index = value->value;
	*p_index = adj_index;

	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_SIZE];
	p_index = value->value;
	*p_index = adj_size;

	value = &entry->match_values[MLXSW_SP_DPIPE_TABLE_ADJ_MATCH_HASH_INDEX];
	p_index = value->value;
	*p_index = adj_hash_index;

	value = &entry->action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_DST_MAC];
	ether_addr_copy(value->value, ha);

	value = &entry->action_values[MLXSW_SP_DPIPE_TABLE_ADJ_ACTION_ERIF_PORT];
	p_rif_value = value->value;
	*p_rif_value = mlxsw_sp_rif_index(rif);
	value->mapping_value = mlxsw_sp_rif_dev_ifindex(rif);
	value->mapping_valid = true;
}