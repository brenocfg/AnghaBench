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
 int REG13_AEC_EN ; 
 int REG13_AGC_EN ; 
 int /*<<< orphan*/  REG_AEC ; 
 int /*<<< orphan*/  REG_HAEC ; 
 int /*<<< orphan*/  REG_REG13 ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7740_set_exp(struct regmap *regmap, int value)
{
	int ret;

	/* Turn off AEC/AGC */
	ret = regmap_update_bits(regmap, REG_REG13,
				 REG13_AEC_EN | REG13_AGC_EN, 0);
	if (ret)
		return ret;

	ret = regmap_write(regmap, REG_AEC, (unsigned char)value);
	if (ret)
		return ret;

	return regmap_write(regmap, REG_HAEC, (unsigned char)(value >> 8));
}