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
struct mlxsw_sp_nve_mc_record {size_t proto; int /*<<< orphan*/  num_entries; struct mlxsw_sp_nve_mc_entry* entries; TYPE_1__* mlxsw_sp; } ;
struct mlxsw_sp_nve_mc_entry {int /*<<< orphan*/  valid; } ;
struct mlxsw_sp_nve {unsigned int* num_max_mc_entries; } ;
struct TYPE_2__ {struct mlxsw_sp_nve* nve; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_record_entry_del (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_record_put (struct mlxsw_sp_nve_mc_record*) ; 

__attribute__((used)) static void
mlxsw_sp_nve_mc_record_delete(struct mlxsw_sp_nve_mc_record *mc_record)
{
	struct mlxsw_sp_nve *nve = mc_record->mlxsw_sp->nve;
	unsigned int num_max_entries;
	int i;

	num_max_entries = nve->num_max_mc_entries[mc_record->proto];
	for (i = 0; i < num_max_entries; i++) {
		struct mlxsw_sp_nve_mc_entry *mc_entry = &mc_record->entries[i];

		if (!mc_entry->valid)
			continue;
		mlxsw_sp_nve_mc_record_entry_del(mc_record, mc_entry);
	}

	WARN_ON(mc_record->num_entries);
	mlxsw_sp_nve_mc_record_put(mc_record);
}