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
struct mt9t001 {int /*<<< orphan*/  ctrls; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mt9t001_power_off (struct mt9t001*) ; 
 int mt9t001_power_on (struct mt9t001*) ; 
 int mt9t001_reset (struct mt9t001*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __mt9t001_set_power(struct mt9t001 *mt9t001, bool on)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	int ret;

	if (!on) {
		mt9t001_power_off(mt9t001);
		return 0;
	}

	ret = mt9t001_power_on(mt9t001);
	if (ret < 0)
		return ret;

	ret = mt9t001_reset(mt9t001);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to reset the camera\n");
		goto e_power;
	}

	ret = v4l2_ctrl_handler_setup(&mt9t001->ctrls);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to set up control handlers\n");
		goto e_power;
	}

	return 0;

e_power:
	mt9t001_power_off(mt9t001);

	return ret;
}