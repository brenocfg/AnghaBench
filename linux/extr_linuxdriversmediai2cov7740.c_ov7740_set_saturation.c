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
 int /*<<< orphan*/  REG_USAT ; 
 int /*<<< orphan*/  REG_VSAT ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7740_set_saturation(struct regmap *regmap, int value)
{
	int ret;

	ret = regmap_write(regmap, REG_USAT, (unsigned char)value);
	if (ret)
		return ret;

	return regmap_write(regmap, REG_VSAT, (unsigned char)value);
}