#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; struct device* dev; } ;
struct bd718xx {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD718XX_PWRBTN_PRESS_DURATION_MASK ; 
 int /*<<< orphan*/  BD718XX_REG_PWRONCONFIG0 ; 
 int /*<<< orphan*/  BD718XX_REG_PWRONCONFIG1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int min (unsigned int,int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bd718xx_init_press_duration(struct bd718xx *bd718xx)
{
	struct device* dev = bd718xx->chip.dev;
	u32 short_press_ms, long_press_ms;
	u32 short_press_value, long_press_value;
	int ret;

	ret = of_property_read_u32(dev->of_node, "rohm,short-press-ms",
				   &short_press_ms);
	if (!ret) {
		short_press_value = min(15u, (short_press_ms + 250) / 500);
		ret = regmap_update_bits(bd718xx->chip.regmap,
					 BD718XX_REG_PWRONCONFIG0,
					 BD718XX_PWRBTN_PRESS_DURATION_MASK,
					 short_press_value);
		if (ret) {
			dev_err(dev, "Failed to init pwron short press\n");
			return ret;
		}
	}

	ret = of_property_read_u32(dev->of_node, "rohm,long-press-ms",
				   &long_press_ms);
	if (!ret) {
		long_press_value = min(15u, (long_press_ms + 500) / 1000);
		ret = regmap_update_bits(bd718xx->chip.regmap,
					 BD718XX_REG_PWRONCONFIG1,
					 BD718XX_PWRBTN_PRESS_DURATION_MASK,
					 long_press_value);
		if (ret) {
			dev_err(dev, "Failed to init pwron long press\n");
			return ret;
		}
	}

	return 0;
}