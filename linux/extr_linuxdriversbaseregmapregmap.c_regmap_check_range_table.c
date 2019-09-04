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
struct regmap_access_table {int /*<<< orphan*/  n_yes_ranges; int /*<<< orphan*/  yes_ranges; int /*<<< orphan*/  n_no_ranges; int /*<<< orphan*/  no_ranges; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int regmap_reg_in_ranges (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool regmap_check_range_table(struct regmap *map, unsigned int reg,
			      const struct regmap_access_table *table)
{
	/* Check "no ranges" first */
	if (regmap_reg_in_ranges(reg, table->no_ranges, table->n_no_ranges))
		return false;

	/* In case zero "yes ranges" are supplied, any reg is OK */
	if (!table->n_yes_ranges)
		return true;

	return regmap_reg_in_ranges(reg, table->yes_ranges,
				    table->n_yes_ranges);
}