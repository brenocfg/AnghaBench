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
struct video_i2c_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMG88XX_PCTL_NORMAL ; 
 int /*<<< orphan*/  AMG88XX_REG_PCTL ; 
 int /*<<< orphan*/  AMG88XX_REG_RST ; 
 int /*<<< orphan*/  AMG88XX_RST_FLAG ; 
 int /*<<< orphan*/  AMG88XX_RST_INIT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int amg88xx_set_power_on(struct video_i2c_data *data)
{
	int ret;

	ret = regmap_write(data->regmap, AMG88XX_REG_PCTL, AMG88XX_PCTL_NORMAL);
	if (ret)
		return ret;

	msleep(50);

	ret = regmap_write(data->regmap, AMG88XX_REG_RST, AMG88XX_RST_INIT);
	if (ret)
		return ret;

	usleep_range(2000, 3000);

	ret = regmap_write(data->regmap, AMG88XX_REG_RST, AMG88XX_RST_FLAG);
	if (ret)
		return ret;

	/*
	 * Wait two frames before reading thermistor and temperature registers
	 */
	msleep(200);

	return 0;
}