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
struct ov5695 {int /*<<< orphan*/  xvclk; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supplies; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5695_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int ov5695_cal_delay (int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __ov5695_power_on(struct ov5695 *ov5695)
{
	int ret;
	u32 delay_us;
	struct device *dev = &ov5695->client->dev;

	ret = clk_prepare_enable(ov5695->xvclk);
	if (ret < 0) {
		dev_err(dev, "Failed to enable xvclk\n");
		return ret;
	}

	gpiod_set_value_cansleep(ov5695->reset_gpio, 1);

	ret = regulator_bulk_enable(OV5695_NUM_SUPPLIES, ov5695->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators\n");
		goto disable_clk;
	}

	gpiod_set_value_cansleep(ov5695->reset_gpio, 0);

	/* 8192 cycles prior to first SCCB transaction */
	delay_us = ov5695_cal_delay(8192);
	usleep_range(delay_us, delay_us * 2);

	return 0;

disable_clk:
	clk_disable_unprepare(ov5695->xvclk);

	return ret;
}