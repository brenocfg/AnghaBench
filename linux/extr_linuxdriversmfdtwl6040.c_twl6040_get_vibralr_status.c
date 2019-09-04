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
typedef  unsigned int u8 ;
struct twl6040 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6040_REG_VIBCTLL ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLR ; 
 unsigned int TWL6040_VIBENA ; 
 unsigned int TWL6040_VIBSEL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int twl6040_get_vibralr_status(struct twl6040 *twl6040)
{
	unsigned int reg;
	int ret;
	u8 status;

	ret = regmap_read(twl6040->regmap, TWL6040_REG_VIBCTLL, &reg);
	if (ret != 0)
		return ret;
	status = reg;

	ret = regmap_read(twl6040->regmap, TWL6040_REG_VIBCTLR, &reg);
	if (ret != 0)
		return ret;
	status |= reg;

	status &= (TWL6040_VIBENA | TWL6040_VIBSEL);

	return status;
}