#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct evergreen_mc_reg_entry {int /*<<< orphan*/ * mc_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ SMC_Evergreen_MCRegisterSet ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cypress_convert_mc_registers(struct evergreen_mc_reg_entry *entry,
					 SMC_Evergreen_MCRegisterSet *data,
					 u32 num_entries, u32 valid_flag)
{
	u32 i, j;

	for (i = 0, j = 0; j < num_entries; j++) {
		if (valid_flag & (1 << j)) {
			data->value[i] = cpu_to_be32(entry->mc_data[j]);
			i++;
		}
	}
}