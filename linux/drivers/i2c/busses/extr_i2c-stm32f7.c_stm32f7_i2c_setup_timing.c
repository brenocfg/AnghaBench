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
struct stm32f7_i2c_setup {size_t speed; char* rise_time; int /*<<< orphan*/  dnf; scalar_t__ analog_filter; int /*<<< orphan*/  fall_time; int /*<<< orphan*/  clock_src; int /*<<< orphan*/  speed_freq; } ;
struct stm32f7_i2c_dev {size_t speed; int /*<<< orphan*/  dev; int /*<<< orphan*/  timing; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t STM32_I2C_SPEED_STANDARD ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* i2c_specs ; 
 int stm32f7_i2c_compute_timing (struct stm32f7_i2c_dev*,struct stm32f7_i2c_setup*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32f7_i2c_setup_timing(struct stm32f7_i2c_dev *i2c_dev,
				    struct stm32f7_i2c_setup *setup)
{
	int ret = 0;

	setup->speed = i2c_dev->speed;
	setup->speed_freq = i2c_specs[setup->speed].rate;
	setup->clock_src = clk_get_rate(i2c_dev->clk);

	if (!setup->clock_src) {
		dev_err(i2c_dev->dev, "clock rate is 0\n");
		return -EINVAL;
	}

	do {
		ret = stm32f7_i2c_compute_timing(i2c_dev, setup,
						 &i2c_dev->timing);
		if (ret) {
			dev_err(i2c_dev->dev,
				"failed to compute I2C timings.\n");
			if (i2c_dev->speed > STM32_I2C_SPEED_STANDARD) {
				i2c_dev->speed--;
				setup->speed = i2c_dev->speed;
				setup->speed_freq =
					i2c_specs[setup->speed].rate;
				dev_warn(i2c_dev->dev,
					 "downgrade I2C Speed Freq to (%i)\n",
					 i2c_specs[setup->speed].rate);
			} else {
				break;
			}
		}
	} while (ret);

	if (ret) {
		dev_err(i2c_dev->dev, "Impossible to compute I2C timings.\n");
		return ret;
	}

	dev_dbg(i2c_dev->dev, "I2C Speed(%i), Freq(%i), Clk Source(%i)\n",
		setup->speed, setup->speed_freq, setup->clock_src);
	dev_dbg(i2c_dev->dev, "I2C Rise(%i) and Fall(%i) Time\n",
		setup->rise_time, setup->fall_time);
	dev_dbg(i2c_dev->dev, "I2C Analog Filter(%s), DNF(%i)\n",
		(setup->analog_filter ? "On" : "Off"), setup->dnf);

	return 0;
}