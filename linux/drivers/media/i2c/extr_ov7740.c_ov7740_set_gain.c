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
 int /*<<< orphan*/  REG13_AGC_EN ; 
 int /*<<< orphan*/  REG15_GAIN_MSB ; 
 int /*<<< orphan*/  REG_CTRL15 ; 
 int /*<<< orphan*/  REG_GAIN ; 
 int /*<<< orphan*/  REG_REG13 ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov7740_set_gain(struct regmap *regmap, int value)
{
	int ret;

	ret = regmap_write(regmap, REG_GAIN, value & 0xff);
	if (ret)
		return ret;

	ret = regmap_update_bits(regmap, REG_CTRL15,
				 REG15_GAIN_MSB, (value >> 8) & 0x3);
	if (!ret)
		ret = regmap_update_bits(regmap, REG_REG13, REG13_AGC_EN, 0);

	return ret;
}