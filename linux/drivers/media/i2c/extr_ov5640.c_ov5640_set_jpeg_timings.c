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
struct ov5640_mode_info {int /*<<< orphan*/  vact; int /*<<< orphan*/  hact; } ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_JPG_MODE_SELECT ; 
 int /*<<< orphan*/  OV5640_REG_VFIFO_HSIZE ; 
 int /*<<< orphan*/  OV5640_REG_VFIFO_VSIZE ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int,int) ; 
 int ov5640_write_reg16 (struct ov5640_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5640_set_jpeg_timings(struct ov5640_dev *sensor,
				   const struct ov5640_mode_info *mode)
{
	int ret;

	/*
	 * compression mode 3 timing
	 *
	 * Data is transmitted with programmable width (VFIFO_HSIZE).
	 * No padding done. Last line may have less data. Varying
	 * number of lines per frame, depending on amount of data.
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_JPG_MODE_SELECT, 0x7, 0x3);
	if (ret < 0)
		return ret;

	ret = ov5640_write_reg16(sensor, OV5640_REG_VFIFO_HSIZE, mode->hact);
	if (ret < 0)
		return ret;

	return ov5640_write_reg16(sensor, OV5640_REG_VFIFO_VSIZE, mode->vact);
}