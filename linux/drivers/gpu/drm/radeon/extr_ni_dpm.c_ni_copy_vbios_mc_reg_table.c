#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ni_mc_reg_table {size_t last; size_t num_entries; TYPE_3__* mc_reg_table_entry; TYPE_1__* mc_reg_address; } ;
struct atom_mc_reg_table {scalar_t__ last; size_t num_entries; TYPE_4__* mc_reg_table_entry; TYPE_2__* mc_reg_address; } ;
struct TYPE_8__ {int /*<<< orphan*/ * mc_data; int /*<<< orphan*/  mclk_max; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mc_data; int /*<<< orphan*/  mclk_max; } ;
struct TYPE_6__ {int /*<<< orphan*/  s1; } ;
struct TYPE_5__ {int /*<<< orphan*/  s1; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAX_AC_TIMING_ENTRIES ; 
 scalar_t__ SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE ; 

__attribute__((used)) static int ni_copy_vbios_mc_reg_table(struct atom_mc_reg_table *table,
				      struct ni_mc_reg_table *ni_table)
{
	u8 i, j;

	if (table->last > SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE)
		return -EINVAL;
	if (table->num_entries > MAX_AC_TIMING_ENTRIES)
		return -EINVAL;

	for (i = 0; i < table->last; i++)
		ni_table->mc_reg_address[i].s1 = table->mc_reg_address[i].s1;
	ni_table->last = table->last;

	for (i = 0; i < table->num_entries; i++) {
		ni_table->mc_reg_table_entry[i].mclk_max =
			table->mc_reg_table_entry[i].mclk_max;
		for (j = 0; j < table->last; j++)
			ni_table->mc_reg_table_entry[i].mc_data[j] =
				table->mc_reg_table_entry[i].mc_data[j];
	}
	ni_table->num_entries = table->num_entries;

	return 0;
}