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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
struct mlxsw_sp_nve_mc_record {size_t proto; TYPE_1__* ops; struct mlxsw_sp_nve_mc_entry* entries; TYPE_2__* mlxsw_sp; } ;
struct mlxsw_sp_nve_mc_entry {int /*<<< orphan*/  valid; } ;
struct mlxsw_sp_nve {unsigned int* num_max_mc_entries; } ;
struct TYPE_4__ {struct mlxsw_sp_nve* nve; } ;
struct TYPE_3__ {scalar_t__ (* entry_compare ) (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*,union mlxsw_sp_l3addr*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct mlxsw_sp_nve_mc_record*,struct mlxsw_sp_nve_mc_entry*,union mlxsw_sp_l3addr*) ; 

__attribute__((used)) static struct mlxsw_sp_nve_mc_entry *
mlxsw_sp_nve_mc_entry_find(struct mlxsw_sp_nve_mc_record *mc_record,
			   union mlxsw_sp_l3addr *addr)
{
	struct mlxsw_sp_nve *nve = mc_record->mlxsw_sp->nve;
	unsigned int num_max_entries;
	int i;

	num_max_entries = nve->num_max_mc_entries[mc_record->proto];
	for (i = 0; i < num_max_entries; i++) {
		struct mlxsw_sp_nve_mc_entry *mc_entry;

		mc_entry = &mc_record->entries[i];
		if (!mc_entry->valid)
			continue;
		if (mc_record->ops->entry_compare(mc_record, mc_entry, addr))
			return mc_entry;
	}

	return NULL;
}