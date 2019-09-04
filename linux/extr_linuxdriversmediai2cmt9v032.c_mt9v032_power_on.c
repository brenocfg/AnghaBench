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
struct mt9v032 {int /*<<< orphan*/  clk; scalar_t__ reset_gpio; int /*<<< orphan*/  sysclk; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9V032_CHIP_CONTROL ; 
 int MT9V032_CHIP_CONTROL_MASTER_MODE ; 
 int /*<<< orphan*/  MT9V032_RESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt9v032_power_on(struct mt9v032 *mt9v032)
{
	struct regmap *map = mt9v032->regmap;
	int ret;

	gpiod_set_value_cansleep(mt9v032->reset_gpio, 1);

	ret = clk_set_rate(mt9v032->clk, mt9v032->sysclk);
	if (ret < 0)
		return ret;

	/* System clock has to be enabled before releasing the reset */
	ret = clk_prepare_enable(mt9v032->clk);
	if (ret)
		return ret;

	udelay(1);

	if (mt9v032->reset_gpio) {
		gpiod_set_value_cansleep(mt9v032->reset_gpio, 0);

		/* After releasing reset we need to wait 10 clock cycles
		 * before accessing the sensor over I2C. As the minimum SYSCLK
		 * frequency is 13MHz, waiting 1µs will be enough in the worst
		 * case.
		 */
		udelay(1);
	}

	/* Reset the chip and stop data read out */
	ret = regmap_write(map, MT9V032_RESET, 1);
	if (ret < 0)
		goto err;

	ret = regmap_write(map, MT9V032_RESET, 0);
	if (ret < 0)
		goto err;

	ret = regmap_write(map, MT9V032_CHIP_CONTROL,
			   MT9V032_CHIP_CONTROL_MASTER_MODE);
	if (ret < 0)
		goto err;

	return 0;

err:
	clk_disable_unprepare(mt9v032->clk);
	return ret;
}