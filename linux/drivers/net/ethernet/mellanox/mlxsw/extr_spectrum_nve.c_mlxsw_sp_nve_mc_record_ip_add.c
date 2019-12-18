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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
struct mlxsw_sp_nve_mc_record {int num_entries; TYPE_1__* ops; } ;
struct mlxsw_sp_nve_mc_entry {int valid; } ;
struct TYPE_2__ {int (* entry_add ) (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*,union mlxsw_sp_l3addr*) ;int /*<<< orphan*/  (* entry_del ) (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list ; 
 struct mlxsw_sp_nve_mc_record* list_prev_entry (struct mlxsw_sp_nve_mc_record*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_nve_mc_entry* mlxsw_sp_nve_mc_free_entry_find (struct mlxsw_sp_nve_mc_record*) ; 
 scalar_t__ mlxsw_sp_nve_mc_record_is_first (struct mlxsw_sp_nve_mc_record*) ; 
 int mlxsw_sp_nve_mc_record_refresh (struct mlxsw_sp_nve_mc_record*) ; 
 int stub1 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*,union mlxsw_sp_l3addr*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ; 

__attribute__((used)) static int
mlxsw_sp_nve_mc_record_ip_add(struct mlxsw_sp_nve_mc_record *mc_record,
			      union mlxsw_sp_l3addr *addr)
{
	struct mlxsw_sp_nve_mc_entry *mc_entry = NULL;
	int err;

	mc_entry = mlxsw_sp_nve_mc_free_entry_find(mc_record);
	if (WARN_ON(!mc_entry))
		return -EINVAL;

	err = mc_record->ops->entry_add(mc_record, mc_entry, addr);
	if (err)
		return err;
	mc_record->num_entries++;
	mc_entry->valid = true;

	err = mlxsw_sp_nve_mc_record_refresh(mc_record);
	if (err)
		goto err_record_refresh;

	/* If this is a new record and not the first one, then we need to
	 * update the next pointer of the previous entry
	 */
	if (mc_record->num_entries != 1 ||
	    mlxsw_sp_nve_mc_record_is_first(mc_record))
		return 0;

	err = mlxsw_sp_nve_mc_record_refresh(list_prev_entry(mc_record, list));
	if (err)
		goto err_prev_record_refresh;

	return 0;

err_prev_record_refresh:
err_record_refresh:
	mc_entry->valid = false;
	mc_record->num_entries--;
	mc_record->ops->entry_del(mc_record, mc_entry);
	return err;
}