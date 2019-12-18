#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sky81452_bl_platform_data {int enable; } ;
struct regmap {int dummy; } ;
struct TYPE_4__ {scalar_t__ brightness; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct backlight_device {TYPE_2__ props; TYPE_1__ dev; } ;

/* Variables and functions */
 int CTZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKY81452_EN ; 
 int /*<<< orphan*/  SKY81452_REG0 ; 
 int /*<<< orphan*/  SKY81452_REG1 ; 
 struct regmap* bl_get_data (struct backlight_device*) ; 
 struct sky81452_bl_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int const) ; 

__attribute__((used)) static int sky81452_bl_update_status(struct backlight_device *bd)
{
	const struct sky81452_bl_platform_data *pdata =
			dev_get_platdata(bd->dev.parent);
	const unsigned int brightness = (unsigned int)bd->props.brightness;
	struct regmap *regmap = bl_get_data(bd);
	int ret;

	if (brightness > 0) {
		ret = regmap_write(regmap, SKY81452_REG0, brightness - 1);
		if (ret < 0)
			return ret;

		return regmap_update_bits(regmap, SKY81452_REG1, SKY81452_EN,
					pdata->enable << CTZ(SKY81452_EN));
	}

	return regmap_update_bits(regmap, SKY81452_REG1, SKY81452_EN, 0);
}