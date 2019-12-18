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
typedef  int u16 ;
struct mt9t001 {int output_control; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T001_OUTPUT_CONTROL ; 
 int mt9t001_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t001_set_output_control(struct mt9t001 *mt9t001, u16 clear,
				      u16 set)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	u16 value = (mt9t001->output_control & ~clear) | set;
	int ret;

	if (value == mt9t001->output_control)
		return 0;

	ret = mt9t001_write(client, MT9T001_OUTPUT_CONTROL, value);
	if (ret < 0)
		return ret;

	mt9t001->output_control = value;
	return 0;
}