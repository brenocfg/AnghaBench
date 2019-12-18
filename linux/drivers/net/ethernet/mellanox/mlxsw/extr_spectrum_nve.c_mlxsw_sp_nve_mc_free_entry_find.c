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
struct mlxsw_sp_nve_mc_record {size_t proto; struct mlxsw_sp_nve_mc_entry* entries; TYPE_1__* mlxsw_sp; } ;
struct mlxsw_sp_nve_mc_entry {scalar_t__ valid; } ;
struct mlxsw_sp_nve {unsigned int* num_max_mc_entries; } ;
struct TYPE_2__ {struct mlxsw_sp_nve* nve; } ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_sp_nve_mc_entry *
mlxsw_sp_nve_mc_free_entry_find(struct mlxsw_sp_nve_mc_record *mc_record)
{
	struct mlxsw_sp_nve *nve = mc_record->mlxsw_sp->nve;
	unsigned int num_max_entries;
	int i;

	num_max_entries = nve->num_max_mc_entries[mc_record->proto];
	for (i = 0; i < num_max_entries; i++) {
		if (mc_record->entries[i].valid)
			continue;
		return &mc_record->entries[i];
	}

	return NULL;
}