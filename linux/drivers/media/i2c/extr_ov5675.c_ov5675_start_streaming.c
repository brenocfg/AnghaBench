#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ov5675_reg_list {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_handler; } ;
struct ov5675 {TYPE_2__ sd; TYPE_1__* cur_mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct ov5675_reg_list reg_list; } ;
struct TYPE_4__ {int link_freq_index; struct ov5675_reg_list reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5675_MODE_STREAMING ; 
 int /*<<< orphan*/  OV5675_REG_MODE_SELECT ; 
 int /*<<< orphan*/  OV5675_REG_VALUE_08BIT ; 
 int __v4l2_ctrl_handler_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* link_freq_configs ; 
 int ov5675_write_reg (struct ov5675*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov5675_write_reg_list (struct ov5675*,struct ov5675_reg_list const*) ; 
 struct i2c_client* v4l2_get_subdevdata (TYPE_2__*) ; 

__attribute__((used)) static int ov5675_start_streaming(struct ov5675 *ov5675)
{
	struct i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	const struct ov5675_reg_list *reg_list;
	int link_freq_index, ret;

	link_freq_index = ov5675->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = ov5675_write_reg_list(ov5675, reg_list);
	if (ret) {
		dev_err(&client->dev, "failed to set plls");
		return ret;
	}

	reg_list = &ov5675->cur_mode->reg_list;
	ret = ov5675_write_reg_list(ov5675, reg_list);
	if (ret) {
		dev_err(&client->dev, "failed to set mode");
		return ret;
	}

	ret = __v4l2_ctrl_handler_setup(ov5675->sd.ctrl_handler);
	if (ret)
		return ret;

	ret = ov5675_write_reg(ov5675, OV5675_REG_MODE_SELECT,
			       OV5675_REG_VALUE_08BIT, OV5675_MODE_STREAMING);
	if (ret) {
		dev_err(&client->dev, "failed to set stream");
		return ret;
	}

	return 0;
}