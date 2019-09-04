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
typedef  int u32 ;
struct ov2685 {int /*<<< orphan*/  xvclk; int /*<<< orphan*/  supplies; TYPE_1__* cur_mode; TYPE_2__* client; int /*<<< orphan*/  reset_gpio; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV2685_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int ov2685_cal_delay (int) ; 
 int ov2685_write_array (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __ov2685_power_on(struct ov2685 *ov2685)
{
	int ret;
	u32 delay_us;
	struct device *dev = &ov2685->client->dev;

	ret = clk_prepare_enable(ov2685->xvclk);
	if (ret < 0) {
		dev_err(dev, "Failed to enable xvclk\n");
		return ret;
	}

	gpiod_set_value_cansleep(ov2685->reset_gpio, 1);

	ret = regulator_bulk_enable(OV2685_NUM_SUPPLIES, ov2685->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators\n");
		goto disable_clk;
	}

	/* The minimum delay between power supplies and reset rising can be 0 */
	gpiod_set_value_cansleep(ov2685->reset_gpio, 0);
	/* 8192 xvclk cycles prior to the first SCCB transaction */
	delay_us = ov2685_cal_delay(8192);
	usleep_range(delay_us, delay_us * 2);

	/* HACK: ov2685 would output messy data after reset(R0103),
	 * writing register before .s_stream() as a workaround
	 */
	ret = ov2685_write_array(ov2685->client, ov2685->cur_mode->reg_list);
	if (ret)
		goto disable_supplies;

	return 0;

disable_supplies:
	regulator_bulk_disable(OV2685_NUM_SUPPLIES, ov2685->supplies);
disable_clk:
	clk_disable_unprepare(ov2685->xvclk);

	return ret;
}