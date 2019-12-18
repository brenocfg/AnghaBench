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
 unsigned int REG13_AGC_EN ; 
 int /*<<< orphan*/  REG_REG13 ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ov7740_set_autogain(struct regmap *regmap, int value)
{
	unsigned int reg;
	int ret;

	ret = regmap_read(regmap, REG_REG13, &reg);
	if (ret)
		return ret;
	if (value)
		reg |= REG13_AGC_EN;
	else
		reg &= ~REG13_AGC_EN;
	return regmap_write(regmap, REG_REG13, reg);
}