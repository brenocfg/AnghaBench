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
typedef  int uint8_t ;
struct iceland_mc_reg_table {int last; int num_entries; int validflag; TYPE_1__* mc_reg_table_entry; } ;
struct TYPE_2__ {scalar_t__* mc_data; } ;

/* Variables and functions */

__attribute__((used)) static int iceland_set_valid_flag(struct iceland_mc_reg_table *table)
{
	uint8_t i, j;
	for (i = 0; i < table->last; i++) {
		for (j = 1; j < table->num_entries; j++) {
			if (table->mc_reg_table_entry[j-1].mc_data[i] !=
				table->mc_reg_table_entry[j].mc_data[i]) {
				table->validflag |= (1<<i);
				break;
			}
		}
	}

	return 0;
}