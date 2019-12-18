#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_nve_mc_record {scalar_t__ num_entries; TYPE_1__* ops; int /*<<< orphan*/  kvdl_index; int /*<<< orphan*/  list; struct mlxsw_sp_nve_mc_list* mc_list; } ;
struct mlxsw_sp_nve_mc_list {int /*<<< orphan*/  records_list; } ;
struct mlxsw_sp_nve_mc_entry {int valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* entry_del ) (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_nve_mc_record* list_next_entry (struct mlxsw_sp_nve_mc_record*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_nve_mc_record* list_prev_entry (struct mlxsw_sp_nve_mc_record*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_nve_mc_record_is_first (struct mlxsw_sp_nve_mc_record*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_record_refresh (struct mlxsw_sp_nve_mc_record*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ; 
 int /*<<< orphan*/  stub3 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ; 
 int /*<<< orphan*/  stub4 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_nve_mc_record_entry_del(struct mlxsw_sp_nve_mc_record *mc_record,
				 struct mlxsw_sp_nve_mc_entry *mc_entry)
{
	struct mlxsw_sp_nve_mc_list *mc_list = mc_record->mc_list;

	mc_entry->valid = false;
	mc_record->num_entries--;

	/* When the record continues to exist we only need to invalidate
	 * the requested entry
	 */
	if (mc_record->num_entries != 0) {
		mlxsw_sp_nve_mc_record_refresh(mc_record);
		mc_record->ops->entry_del(mc_record, mc_entry);
		return;
	}

	/* If the record needs to be deleted, but it is not the first,
	 * then we need to make sure that the previous record no longer
	 * points to it. Remove deleted record from the list to reflect
	 * that and then re-add it at the end, so that it could be
	 * properly removed by the record destruction code
	 */
	if (!mlxsw_sp_nve_mc_record_is_first(mc_record)) {
		struct mlxsw_sp_nve_mc_record *prev_record;

		prev_record = list_prev_entry(mc_record, list);
		list_del(&mc_record->list);
		mlxsw_sp_nve_mc_record_refresh(prev_record);
		list_add_tail(&mc_record->list, &mc_list->records_list);
		mc_record->ops->entry_del(mc_record, mc_entry);
		return;
	}

	/* If the first record needs to be deleted, but the list is not
	 * singular, then the second record needs to be written in the
	 * first record's address, as this address is stored as a property
	 * of the FID
	 */
	if (mlxsw_sp_nve_mc_record_is_first(mc_record) &&
	    !list_is_singular(&mc_list->records_list)) {
		struct mlxsw_sp_nve_mc_record *next_record;

		next_record = list_next_entry(mc_record, list);
		swap(mc_record->kvdl_index, next_record->kvdl_index);
		mlxsw_sp_nve_mc_record_refresh(next_record);
		mc_record->ops->entry_del(mc_record, mc_entry);
		return;
	}

	/* This is the last case where the last remaining record needs to
	 * be deleted. Simply delete the entry
	 */
	mc_record->ops->entry_del(mc_record, mc_entry);
}