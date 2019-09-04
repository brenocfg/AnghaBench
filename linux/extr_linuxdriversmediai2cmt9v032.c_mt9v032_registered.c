#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct mt9v032 {TYPE_1__* version; int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  MT9V032_CHIP_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mt9v032_configure_pixel_rate (struct mt9v032*) ; 
 int /*<<< orphan*/  mt9v032_power_off (struct mt9v032*) ; 
 int mt9v032_power_on (struct mt9v032*) ; 
 TYPE_1__* mt9v032_versions ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct mt9v032* to_mt9v032 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v032_registered(struct v4l2_subdev *subdev)
{
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);
	unsigned int i;
	u32 version;
	int ret;

	dev_info(&client->dev, "Probing MT9V032 at address 0x%02x\n",
			client->addr);

	ret = mt9v032_power_on(mt9v032);
	if (ret < 0) {
		dev_err(&client->dev, "MT9V032 power up failed\n");
		return ret;
	}

	/* Read and check the sensor version */
	ret = regmap_read(mt9v032->regmap, MT9V032_CHIP_VERSION, &version);

	mt9v032_power_off(mt9v032);

	if (ret < 0) {
		dev_err(&client->dev, "Failed reading chip version\n");
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(mt9v032_versions); ++i) {
		if (mt9v032_versions[i].version == version) {
			mt9v032->version = &mt9v032_versions[i];
			break;
		}
	}

	if (mt9v032->version == NULL) {
		dev_err(&client->dev, "Unsupported chip version 0x%04x\n",
			version);
		return -ENODEV;
	}

	dev_info(&client->dev, "%s detected at address 0x%02x\n",
		 mt9v032->version->name, client->addr);

	mt9v032_configure_pixel_rate(mt9v032);

	return ret;
}