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
struct regmap_field {unsigned int mask; unsigned int shift; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int regmap_field_read(struct regmap_field *field, unsigned int *val)
{
	int ret;
	unsigned int reg_val;
	ret = regmap_read(field->regmap, field->reg, &reg_val);
	if (ret != 0)
		return ret;

	reg_val &= field->mask;
	reg_val >>= field->shift;
	*val = reg_val;

	return ret;
}