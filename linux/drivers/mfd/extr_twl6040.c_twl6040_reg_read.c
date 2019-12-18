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
struct twl6040 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

int twl6040_reg_read(struct twl6040 *twl6040, unsigned int reg)
{
	int ret;
	unsigned int val;

	ret = regmap_read(twl6040->regmap, reg, &val);
	if (ret < 0)
		return ret;

	return val;
}