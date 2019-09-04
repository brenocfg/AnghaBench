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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct et8ek8_sensor {unsigned int xclk_freq; int /*<<< orphan*/  reset; int /*<<< orphan*/  ext_clk; TYPE_2__* current_reglist; int /*<<< orphan*/  vana; struct v4l2_subdev subdev; } ;
struct TYPE_3__ {unsigned int ext_clock; } ;
struct TYPE_4__ {TYPE_1__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET8EK8_REGLIST_POWERON ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int et8ek8_i2c_reglist_find_write (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et8ek8_power_off (struct et8ek8_sensor*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  meta_reglist ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int et8ek8_power_on(struct et8ek8_sensor *sensor)
{
	struct v4l2_subdev *subdev = &sensor->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	unsigned int xclk_freq;
	int val, rval;

	rval = regulator_enable(sensor->vana);
	if (rval) {
		dev_err(&client->dev, "failed to enable vana regulator\n");
		return rval;
	}

	if (sensor->current_reglist)
		xclk_freq = sensor->current_reglist->mode.ext_clock;
	else
		xclk_freq = sensor->xclk_freq;

	rval = clk_set_rate(sensor->ext_clk, xclk_freq);
	if (rval < 0) {
		dev_err(&client->dev, "unable to set extclk clock freq to %u\n",
			xclk_freq);
		goto out;
	}
	rval = clk_prepare_enable(sensor->ext_clk);
	if (rval < 0) {
		dev_err(&client->dev, "failed to enable extclk\n");
		goto out;
	}

	if (rval)
		goto out;

	udelay(10); /* I wish this is a good value */

	gpiod_set_value(sensor->reset, 1);

	msleep(5000 * 1000 / xclk_freq + 1); /* Wait 5000 cycles */

	rval = et8ek8_i2c_reglist_find_write(client, &meta_reglist,
					     ET8EK8_REGLIST_POWERON);
	if (rval)
		goto out;

#ifdef USE_CRC
	rval = et8ek8_i2c_read_reg(client, ET8EK8_REG_8BIT, 0x1263, &val);
	if (rval)
		goto out;
#if USE_CRC /* TODO get crc setting from DT */
	val |= BIT(4);
#else
	val &= ~BIT(4);
#endif
	rval = et8ek8_i2c_write_reg(client, ET8EK8_REG_8BIT, 0x1263, val);
	if (rval)
		goto out;
#endif

out:
	if (rval)
		et8ek8_power_off(sensor);

	return rval;
}