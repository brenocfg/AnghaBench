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
 int /*<<< orphan*/  SC27XX_BLTC_EN ; 
 int /*<<< orphan*/  SC27XX_CLK_EN0 ; 
 int /*<<< orphan*/  SC27XX_MODULE_EN0 ; 
 int /*<<< orphan*/  SC27XX_RGB_CTRL ; 
 int /*<<< orphan*/  SC27XX_RGB_PD ; 
 int /*<<< orphan*/  SC27XX_RTC_EN ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sc27xx_led_init(struct regmap *regmap)
{
	int err;

	err = regmap_update_bits(regmap, SC27XX_MODULE_EN0, SC27XX_BLTC_EN,
				 SC27XX_BLTC_EN);
	if (err)
		return err;

	err = regmap_update_bits(regmap, SC27XX_CLK_EN0, SC27XX_RTC_EN,
				 SC27XX_RTC_EN);
	if (err)
		return err;

	return regmap_update_bits(regmap, SC27XX_RGB_CTRL, SC27XX_RGB_PD, 0);
}