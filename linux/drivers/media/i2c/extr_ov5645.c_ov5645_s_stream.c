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
struct v4l2_subdev {int dummy; } ;
struct ov5645 {int /*<<< orphan*/  dev; int /*<<< orphan*/  ctrls; TYPE_1__* current_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_IO_MIPI_CTRL00 ; 
 int /*<<< orphan*/  OV5645_SYSTEM_CTRL0 ; 
 int OV5645_SYSTEM_CTRL0_START ; 
 int OV5645_SYSTEM_CTRL0_STOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int ov5645_set_register_array (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int) ; 
 struct ov5645* to_ov5645 (struct v4l2_subdev*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5645_s_stream(struct v4l2_subdev *subdev, int enable)
{
	struct ov5645 *ov5645 = to_ov5645(subdev);
	int ret;

	if (enable) {
		ret = ov5645_set_register_array(ov5645,
					ov5645->current_mode->data,
					ov5645->current_mode->data_size);
		if (ret < 0) {
			dev_err(ov5645->dev, "could not set mode %dx%d\n",
				ov5645->current_mode->width,
				ov5645->current_mode->height);
			return ret;
		}
		ret = v4l2_ctrl_handler_setup(&ov5645->ctrls);
		if (ret < 0) {
			dev_err(ov5645->dev, "could not sync v4l2 controls\n");
			return ret;
		}

		ret = ov5645_write_reg(ov5645, OV5645_IO_MIPI_CTRL00, 0x45);
		if (ret < 0)
			return ret;

		ret = ov5645_write_reg(ov5645, OV5645_SYSTEM_CTRL0,
				       OV5645_SYSTEM_CTRL0_START);
		if (ret < 0)
			return ret;
	} else {
		ret = ov5645_write_reg(ov5645, OV5645_IO_MIPI_CTRL00, 0x40);
		if (ret < 0)
			return ret;

		ret = ov5645_write_reg(ov5645, OV5645_SYSTEM_CTRL0,
				       OV5645_SYSTEM_CTRL0_STOP);
		if (ret < 0)
			return ret;
	}

	return 0;
}