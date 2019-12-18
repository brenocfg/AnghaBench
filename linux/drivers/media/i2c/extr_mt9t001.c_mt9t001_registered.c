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
struct v4l2_subdev {int dummy; } ;
struct mt9t001 {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MT9T001_CHIP_ID ; 
 int /*<<< orphan*/  MT9T001_CHIP_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t001_power_off (struct mt9t001*) ; 
 int mt9t001_power_on (struct mt9t001*) ; 
 scalar_t__ mt9t001_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct mt9t001* to_mt9t001 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t001_registered(struct v4l2_subdev *subdev)
{
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	struct mt9t001 *mt9t001 = to_mt9t001(subdev);
	s32 data;
	int ret;

	ret = mt9t001_power_on(mt9t001);
	if (ret < 0) {
		dev_err(&client->dev, "MT9T001 power up failed\n");
		return ret;
	}

	/* Read out the chip version register */
	data = mt9t001_read(client, MT9T001_CHIP_VERSION);
	mt9t001_power_off(mt9t001);

	if (data != MT9T001_CHIP_ID) {
		dev_err(&client->dev,
			"MT9T001 not detected, wrong version 0x%04x\n", data);
		return -ENODEV;
	}

	dev_info(&client->dev, "MT9T001 detected at address 0x%02x\n",
		 client->addr);

	return 0;
}