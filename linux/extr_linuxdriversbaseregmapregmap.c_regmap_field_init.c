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
struct regmap_field {int /*<<< orphan*/  id_offset; int /*<<< orphan*/  id_size; int /*<<< orphan*/  mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  reg; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct reg_field {int /*<<< orphan*/  id_offset; int /*<<< orphan*/  id_size; int /*<<< orphan*/  lsb; int /*<<< orphan*/  msb; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regmap_field_init(struct regmap_field *rm_field,
	struct regmap *regmap, struct reg_field reg_field)
{
	rm_field->regmap = regmap;
	rm_field->reg = reg_field.reg;
	rm_field->shift = reg_field.lsb;
	rm_field->mask = GENMASK(reg_field.msb, reg_field.lsb);
	rm_field->id_size = reg_field.id_size;
	rm_field->id_offset = reg_field.id_offset;
}