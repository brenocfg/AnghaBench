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
struct mt9m111 {int /*<<< orphan*/  gain; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int MT9M111_RESET_ANALOG_STANDBY ; 
 int /*<<< orphan*/  MT9M111_RESET_CHIP_ENABLE ; 
 int MT9M111_RESET_OUTPUT_DISABLE ; 
 int MT9M111_RESET_RESET_MODE ; 
 int MT9M111_RESET_RESET_SOC ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  mt9m111_get_global_gain (struct mt9m111*) ; 
 int reg_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_suspend(struct mt9m111 *mt9m111)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	int ret;

	v4l2_ctrl_s_ctrl(mt9m111->gain, mt9m111_get_global_gain(mt9m111));

	ret = reg_set(RESET, MT9M111_RESET_RESET_MODE);
	if (!ret)
		ret = reg_set(RESET, MT9M111_RESET_RESET_SOC |
			      MT9M111_RESET_OUTPUT_DISABLE |
			      MT9M111_RESET_ANALOG_STANDBY);
	if (!ret)
		ret = reg_clear(RESET, MT9M111_RESET_CHIP_ENABLE);

	return ret;
}