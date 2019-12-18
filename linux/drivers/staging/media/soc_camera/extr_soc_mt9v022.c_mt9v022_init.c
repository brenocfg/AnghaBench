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
struct mt9v022 {int chip_control; int /*<<< orphan*/  hdl; TYPE_1__* reg; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_total_shutter_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9V022_AEC_AGC_ENABLE ; 
 int /*<<< orphan*/  MT9V022_ANALOG_GAIN ; 
 int /*<<< orphan*/  MT9V022_BLACK_LEVEL_CALIB_CTRL ; 
 int /*<<< orphan*/  MT9V022_CHIP_CONTROL ; 
 int /*<<< orphan*/  MT9V022_DIGITAL_TEST_PATTERN ; 
 int /*<<< orphan*/  MT9V022_READ_MODE ; 
 int /*<<< orphan*/  MT9V022_TOTAL_SHUTTER_WIDTH ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct mt9v022* to_mt9v022 (struct i2c_client*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9v022_init(struct i2c_client *client)
{
	struct mt9v022 *mt9v022 = to_mt9v022(client);
	int ret;

	/*
	 * Almost the default mode: master, parallel, simultaneous, and an
	 * undocumented bit 0x200, which is present in table 7, but not in 8,
	 * plus snapshot mode to disable scan for now
	 */
	mt9v022->chip_control |= 0x10;
	ret = reg_write(client, MT9V022_CHIP_CONTROL, mt9v022->chip_control);
	if (!ret)
		ret = reg_write(client, MT9V022_READ_MODE, 0x300);

	/* All defaults */
	if (!ret)
		/* AEC, AGC on */
		ret = reg_set(client, MT9V022_AEC_AGC_ENABLE, 0x3);
	if (!ret)
		ret = reg_write(client, MT9V022_ANALOG_GAIN, 16);
	if (!ret)
		ret = reg_write(client, MT9V022_TOTAL_SHUTTER_WIDTH, 480);
	if (!ret)
		ret = reg_write(client, mt9v022->reg->max_total_shutter_width, 480);
	if (!ret)
		/* default - auto */
		ret = reg_clear(client, MT9V022_BLACK_LEVEL_CALIB_CTRL, 1);
	if (!ret)
		ret = reg_write(client, MT9V022_DIGITAL_TEST_PATTERN, 0);
	if (!ret)
		return v4l2_ctrl_handler_setup(&mt9v022->hdl);

	return ret;
}