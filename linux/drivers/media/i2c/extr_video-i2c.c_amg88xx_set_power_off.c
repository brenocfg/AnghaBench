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
 int /*<<< orphan*/  AMG88XX_PCTL_SLEEP ; 
 int /*<<< orphan*/  AMG88XX_REG_PCTL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amg88xx_set_power_off(struct video_i2c_data *data)
{
	int ret;

	ret = regmap_write(data->regmap, AMG88XX_REG_PCTL, AMG88XX_PCTL_SLEEP);
	if (ret)
		return ret;
	/*
	 * Wait for a while to avoid resuming normal mode immediately after
	 * entering sleep mode, otherwise the device occasionally goes wrong
	 * (thermistor and temperature registers are not updated at all)
	 */
	msleep(100);

	return 0;
}