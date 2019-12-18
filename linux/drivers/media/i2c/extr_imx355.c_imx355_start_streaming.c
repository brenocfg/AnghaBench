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
struct imx355_reg_list {int /*<<< orphan*/  num_of_regs; int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_handler; } ;
struct imx355 {TYPE_2__ sd; TYPE_1__* cur_mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct imx355_reg_list reg_list; } ;

/* Variables and functions */
 int IMX355_MODE_STREAMING ; 
 int /*<<< orphan*/  IMX355_REG_DPGA_USE_GLOBAL_GAIN ; 
 int /*<<< orphan*/  IMX355_REG_MODE_SELECT ; 
 int __v4l2_ctrl_handler_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct imx355_reg_list imx355_global_setting ; 
 int imx355_write_reg (struct imx355*,int /*<<< orphan*/ ,int,int) ; 
 int imx355_write_regs (struct imx355*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (TYPE_2__*) ; 

__attribute__((used)) static int imx355_start_streaming(struct imx355 *imx355)
{
	struct i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	const struct imx355_reg_list *reg_list;
	int ret;

	/* Global Setting */
	reg_list = &imx355_global_setting;
	ret = imx355_write_regs(imx355, reg_list->regs, reg_list->num_of_regs);
	if (ret) {
		dev_err(&client->dev, "failed to set global settings");
		return ret;
	}

	/* Apply default values of current mode */
	reg_list = &imx355->cur_mode->reg_list;
	ret = imx355_write_regs(imx355, reg_list->regs, reg_list->num_of_regs);
	if (ret) {
		dev_err(&client->dev, "failed to set mode");
		return ret;
	}

	/* set digital gain control to all color mode */
	ret = imx355_write_reg(imx355, IMX355_REG_DPGA_USE_GLOBAL_GAIN, 1, 1);
	if (ret)
		return ret;

	/* Apply customized values from user */
	ret =  __v4l2_ctrl_handler_setup(imx355->sd.ctrl_handler);
	if (ret)
		return ret;

	return imx355_write_reg(imx355, IMX355_REG_MODE_SELECT,
				1, IMX355_MODE_STREAMING);
}