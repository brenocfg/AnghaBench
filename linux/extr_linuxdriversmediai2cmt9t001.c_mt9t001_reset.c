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
struct mt9t001 {int /*<<< orphan*/  output_control; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T001_OUTPUT_CONTROL_CHIP_ENABLE ; 
 int /*<<< orphan*/  MT9T001_OUTPUT_CONTROL_DEF ; 
 int /*<<< orphan*/  MT9T001_RESET ; 
 int mt9t001_set_output_control (struct mt9t001*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt9t001_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t001_reset(struct mt9t001 *mt9t001)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	int ret;

	/* Reset the chip and stop data read out */
	ret = mt9t001_write(client, MT9T001_RESET, 1);
	if (ret < 0)
		return ret;

	ret = mt9t001_write(client, MT9T001_RESET, 0);
	if (ret < 0)
		return ret;

	mt9t001->output_control = MT9T001_OUTPUT_CONTROL_DEF;

	return mt9t001_set_output_control(mt9t001,
					  MT9T001_OUTPUT_CONTROL_CHIP_ENABLE,
					  0);
}