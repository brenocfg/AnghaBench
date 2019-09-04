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
struct s5k6a3 {int /*<<< orphan*/  dev; TYPE_1__* supplies; int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  clock; int /*<<< orphan*/  clock_frequency; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int S5K6A3_NUM_SUPPLIES ; 
 int S5K6A3_SUPP_VDDA ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __s5k6a3_power_on(struct s5k6a3 *sensor)
{
	int i = S5K6A3_SUPP_VDDA;
	int ret;

	ret = clk_set_rate(sensor->clock, sensor->clock_frequency);
	if (ret < 0)
		return ret;

	ret = pm_runtime_get(sensor->dev);
	if (ret < 0)
		return ret;

	ret = regulator_enable(sensor->supplies[i].consumer);
	if (ret < 0)
		goto error_rpm_put;

	ret = clk_prepare_enable(sensor->clock);
	if (ret < 0)
		goto error_reg_dis;

	for (i++; i < S5K6A3_NUM_SUPPLIES; i++) {
		ret = regulator_enable(sensor->supplies[i].consumer);
		if (ret < 0)
			goto error_reg_dis;
	}

	gpio_set_value(sensor->gpio_reset, 1);
	usleep_range(600, 800);
	gpio_set_value(sensor->gpio_reset, 0);
	usleep_range(600, 800);
	gpio_set_value(sensor->gpio_reset, 1);

	/* Delay needed for the sensor initialization */
	msleep(20);
	return 0;

error_reg_dis:
	for (--i; i >= 0; --i)
		regulator_disable(sensor->supplies[i].consumer);
error_rpm_put:
	pm_runtime_put(sensor->dev);
	return ret;
}