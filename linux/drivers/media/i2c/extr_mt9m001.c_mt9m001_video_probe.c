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
struct mt9m001 {int /*<<< orphan*/  hdl; int /*<<< orphan*/ * fmts; int /*<<< orphan*/ * fmt; void* num_fmts; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  MT9M001_CHIP_ENABLE ; 
 int /*<<< orphan*/  MT9M001_CHIP_VERSION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,char*) ; 
 void* mt9m001_colour_fmts ; 
 int mt9m001_init (struct i2c_client*) ; 
 void* mt9m001_monochrome_fmts ; 
 int reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m001_video_probe(struct i2c_client *client)
{
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	s32 data;
	int ret;

	/* Enable the chip */
	data = reg_write(client, MT9M001_CHIP_ENABLE, 1);
	dev_dbg(&client->dev, "write: %d\n", data);

	/* Read out the chip version register */
	data = reg_read(client, MT9M001_CHIP_VERSION);

	/* must be 0x8411 or 0x8421 for colour sensor and 8431 for bw */
	switch (data) {
	case 0x8411:
	case 0x8421:
		mt9m001->fmts = mt9m001_colour_fmts;
		mt9m001->num_fmts = ARRAY_SIZE(mt9m001_colour_fmts);
		break;
	case 0x8431:
		mt9m001->fmts = mt9m001_monochrome_fmts;
		mt9m001->num_fmts = ARRAY_SIZE(mt9m001_monochrome_fmts);
		break;
	default:
		dev_err(&client->dev,
			"No MT9M001 chip detected, register read %x\n", data);
		ret = -ENODEV;
		goto done;
	}

	mt9m001->fmt = &mt9m001->fmts[0];

	dev_info(&client->dev, "Detected a MT9M001 chip ID %x (%s)\n", data,
		 data == 0x8431 ? "C12STM" : "C12ST");

	ret = mt9m001_init(client);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to initialise the camera\n");
		goto done;
	}

	/* mt9m001_init() has reset the chip, returning registers to defaults */
	ret = v4l2_ctrl_handler_setup(&mt9m001->hdl);

done:
	return ret;
}