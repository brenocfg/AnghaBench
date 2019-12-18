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
struct regulator_bulk_data {char* supply; } ;

/* Variables and functions */

void regulator_bulk_set_supply_names(struct regulator_bulk_data *consumers,
				     const char *const *supply_names,
				     unsigned int num_supplies)
{
	unsigned int i;

	for (i = 0; i < num_supplies; i++)
		consumers[i].supply = supply_names[i];
}