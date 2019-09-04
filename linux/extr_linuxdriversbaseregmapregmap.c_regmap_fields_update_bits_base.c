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
struct regmap_field {unsigned int id_size; unsigned int shift; unsigned int mask; unsigned int id_offset; scalar_t__ reg; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int regmap_update_bits_base (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int,int*,int,int) ; 

int regmap_fields_update_bits_base(struct regmap_field *field,  unsigned int id,
				   unsigned int mask, unsigned int val,
				   bool *change, bool async, bool force)
{
	if (id >= field->id_size)
		return -EINVAL;

	mask = (mask << field->shift) & field->mask;

	return regmap_update_bits_base(field->regmap,
				       field->reg + (field->id_offset * id),
				       mask, val << field->shift,
				       change, async, force);
}