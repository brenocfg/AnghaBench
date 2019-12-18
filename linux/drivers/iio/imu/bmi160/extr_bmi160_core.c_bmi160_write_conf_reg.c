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
struct regmap {int dummy; } ;

/* Variables and functions */
 int regmap_read (struct regmap*,unsigned int,unsigned int*) ; 
 int regmap_write (struct regmap*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

__attribute__((used)) static int bmi160_write_conf_reg(struct regmap *regmap, unsigned int reg,
				 unsigned int mask, unsigned int bits,
				 unsigned int write_usleep)
{
	int ret;
	unsigned int val;

	ret = regmap_read(regmap, reg, &val);
	if (ret)
		return ret;

	val = (val & ~mask) | bits;

	ret = regmap_write(regmap, reg, val);
	if (ret)
		return ret;

	/*
	 * We need to wait after writing before we can write again. See the
	 * datasheet, page 93.
	 */
	usleep_range(write_usleep, write_usleep + 1000);

	return 0;
}