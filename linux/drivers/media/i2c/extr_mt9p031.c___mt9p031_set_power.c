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
struct mt9p031 {int /*<<< orphan*/  ctrls; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mt9p031_power_off (struct mt9p031*) ; 
 int mt9p031_power_on (struct mt9p031*) ; 
 int mt9p031_reset (struct mt9p031*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __mt9p031_set_power(struct mt9p031 *mt9p031, bool on)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	int ret;

	if (!on) {
		mt9p031_power_off(mt9p031);
		return 0;
	}

	ret = mt9p031_power_on(mt9p031);
	if (ret < 0)
		return ret;

	ret = mt9p031_reset(mt9p031);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to reset the camera\n");
		return ret;
	}

	return v4l2_ctrl_handler_setup(&mt9p031->ctrls);
}