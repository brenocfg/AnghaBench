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
typedef  int u8 ;
struct v4l2_subdev {int /*<<< orphan*/  dev; } ;
struct tvp5150 {int dev_id; int rom_ver; struct v4l2_subdev sd; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ TVP5150_MSB_DEV_ID ; 
 int /*<<< orphan*/  TVP5150_REV_SELECT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int tvp5150_read (struct v4l2_subdev*,scalar_t__) ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_detect_version(struct tvp5150 *core)
{
	struct v4l2_subdev *sd = &core->sd;
	struct i2c_client *c = v4l2_get_subdevdata(sd);
	unsigned int i;
	u8 regs[4];
	int res;

	/*
	 * Read consequent registers - TVP5150_MSB_DEV_ID, TVP5150_LSB_DEV_ID,
	 * TVP5150_ROM_MAJOR_VER, TVP5150_ROM_MINOR_VER
	 */
	for (i = 0; i < 4; i++) {
		res = tvp5150_read(sd, TVP5150_MSB_DEV_ID + i);
		if (res < 0)
			return res;
		regs[i] = res;
	}

	core->dev_id = (regs[0] << 8) | regs[1];
	core->rom_ver = (regs[2] << 8) | regs[3];

	dev_info(sd->dev, "tvp%04x (%u.%u) chip found @ 0x%02x (%s)\n",
		  core->dev_id, regs[2], regs[3], c->addr << 1,
		  c->adapter->name);

	if (core->dev_id == 0x5150 && core->rom_ver == 0x0321) {
		dev_info(sd->dev, "tvp5150a detected.\n");
	} else if (core->dev_id == 0x5150 && core->rom_ver == 0x0400) {
		dev_info(sd->dev, "tvp5150am1 detected.\n");

		/* ITU-T BT.656.4 timing */
		tvp5150_write(sd, TVP5150_REV_SELECT, 0);
	} else if (core->dev_id == 0x5151 && core->rom_ver == 0x0100) {
		dev_info(sd->dev, "tvp5151 detected.\n");
	} else {
		dev_info(sd->dev, "*** unknown tvp%04x chip detected.\n",
			  core->dev_id);
	}

	return 0;
}