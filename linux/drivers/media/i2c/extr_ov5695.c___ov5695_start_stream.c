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
struct ov5695 {int /*<<< orphan*/  client; int /*<<< orphan*/  ctrl_handler; TYPE_1__* cur_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5695_MODE_STREAMING ; 
 int /*<<< orphan*/  OV5695_REG_CTRL_MODE ; 
 int /*<<< orphan*/  OV5695_REG_VALUE_08BIT ; 
 int __v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov5695_global_regs ; 
 int ov5695_write_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov5695_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ov5695_start_stream(struct ov5695 *ov5695)
{
	int ret;

	ret = ov5695_write_array(ov5695->client, ov5695_global_regs);
	if (ret)
		return ret;
	ret = ov5695_write_array(ov5695->client, ov5695->cur_mode->reg_list);
	if (ret)
		return ret;

	/* In case these controls are set before streaming */
	ret = __v4l2_ctrl_handler_setup(&ov5695->ctrl_handler);
	if (ret)
		return ret;

	return ov5695_write_reg(ov5695->client, OV5695_REG_CTRL_MODE,
				OV5695_REG_VALUE_08BIT, OV5695_MODE_STREAMING);
}