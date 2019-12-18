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
struct ov5645 {int /*<<< orphan*/  rst_gpio; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  supplies; int /*<<< orphan*/  dev; int /*<<< orphan*/  xclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_NUM_SUPPLIES ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov5645_set_power_on(struct ov5645 *ov5645)
{
	int ret;

	ret = regulator_bulk_enable(OV5645_NUM_SUPPLIES, ov5645->supplies);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(ov5645->xclk);
	if (ret < 0) {
		dev_err(ov5645->dev, "clk prepare enable failed\n");
		regulator_bulk_disable(OV5645_NUM_SUPPLIES, ov5645->supplies);
		return ret;
	}

	usleep_range(5000, 15000);
	gpiod_set_value_cansleep(ov5645->enable_gpio, 1);

	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ov5645->rst_gpio, 0);

	msleep(20);

	return 0;
}