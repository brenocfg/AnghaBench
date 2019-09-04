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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_FRAME_CTRL01 ; 
 int /*<<< orphan*/  OV5640_REG_IO_MIPI_CTRL00 ; 
 int ov5640_write_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5640_set_stream_mipi(struct ov5640_dev *sensor, bool on)
{
	int ret;

	/*
	 * Enable/disable the MIPI interface
	 *
	 * 0x300e = on ? 0x45 : 0x40
	 *
	 * FIXME: the sensor manual (version 2.03) reports
	 * [7:5] = 000  : 1 data lane mode
	 * [7:5] = 001  : 2 data lanes mode
	 * But this settings do not work, while the following ones
	 * have been validated for 2 data lanes mode.
	 *
	 * [7:5] = 010	: 2 data lanes mode
	 * [4] = 0	: Power up MIPI HS Tx
	 * [3] = 0	: Power up MIPI LS Rx
	 * [2] = 1/0	: MIPI interface enable/disable
	 * [1:0] = 01/00: FIXME: 'debug'
	 */
	ret = ov5640_write_reg(sensor, OV5640_REG_IO_MIPI_CTRL00,
			       on ? 0x45 : 0x40);
	if (ret)
		return ret;

	return ov5640_write_reg(sensor, OV5640_REG_FRAME_CTRL01,
				on ? 0x00 : 0x0f);
}