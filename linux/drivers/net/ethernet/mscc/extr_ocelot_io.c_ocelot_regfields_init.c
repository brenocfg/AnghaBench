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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct reg_field {size_t reg; int /*<<< orphan*/  msb; int /*<<< orphan*/  lsb; } ;
struct ocelot {size_t** map; int /*<<< orphan*/ * regfields; int /*<<< orphan*/ * targets; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int REGFIELD_MAX ; 
 size_t REG_MASK ; 
 size_t TARGET_OFFSET ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct reg_field) ; 

int ocelot_regfields_init(struct ocelot *ocelot,
			  const struct reg_field *const regfields)
{
	unsigned int i;
	u16 target;

	for (i = 0; i < REGFIELD_MAX; i++) {
		struct reg_field regfield = {};
		u32 reg = regfields[i].reg;

		if (!reg)
			continue;

		target = regfields[i].reg >> TARGET_OFFSET;

		regfield.reg = ocelot->map[target][reg & REG_MASK];
		regfield.lsb = regfields[i].lsb;
		regfield.msb = regfields[i].msb;

		ocelot->regfields[i] =
		devm_regmap_field_alloc(ocelot->dev,
					ocelot->targets[target],
					regfield);

		if (IS_ERR(ocelot->regfields[i]))
			return PTR_ERR(ocelot->regfields[i]);
	}

	return 0;
}