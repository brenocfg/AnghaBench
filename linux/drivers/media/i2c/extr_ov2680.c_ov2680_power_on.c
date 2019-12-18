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
struct ov2680_dev {int is_enabled; int /*<<< orphan*/  xvclk; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supplies; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV2680_NUM_SUPPLIES ; 
 int /*<<< orphan*/  OV2680_REG_SOFT_RESET ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  ov2680_power_down (struct ov2680_dev*) ; 
 int /*<<< orphan*/  ov2680_power_up (struct ov2680_dev*) ; 
 int /*<<< orphan*/  ov2680_stream_disable (struct ov2680_dev*) ; 
 int /*<<< orphan*/  ov2680_stream_enable (struct ov2680_dev*) ; 
 struct device* ov2680_to_dev (struct ov2680_dev*) ; 
 int ov2680_write_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov2680_power_on(struct ov2680_dev *sensor)
{
	struct device *dev = ov2680_to_dev(sensor);
	int ret;

	if (sensor->is_enabled)
		return 0;

	ret = regulator_bulk_enable(OV2680_NUM_SUPPLIES, sensor->supplies);
	if (ret < 0) {
		dev_err(dev, "failed to enable regulators: %d\n", ret);
		return ret;
	}

	if (!sensor->reset_gpio) {
		ret = ov2680_write_reg(sensor, OV2680_REG_SOFT_RESET, 0x01);
		if (ret != 0) {
			dev_err(dev, "sensor soft reset failed\n");
			return ret;
		}
		usleep_range(1000, 2000);
	} else {
		ov2680_power_down(sensor);
		ov2680_power_up(sensor);
	}

	ret = clk_prepare_enable(sensor->xvclk);
	if (ret < 0)
		return ret;

	sensor->is_enabled = true;

	/* Set clock lane into LP-11 state */
	ov2680_stream_enable(sensor);
	usleep_range(1000, 2000);
	ov2680_stream_disable(sensor);

	return 0;
}