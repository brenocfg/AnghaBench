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
struct v4l2_subdev {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  cs3308_ops ; 
 int /*<<< orphan*/  cs3308_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 struct v4l2_subdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs3308_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct v4l2_subdev *sd;
	unsigned i;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	if ((i2c_smbus_read_byte_data(client, 0x1c) & 0xf0) != 0xe0)
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
		 client->addr << 1, client->adapter->name);

	sd = kzalloc(sizeof(struct v4l2_subdev), GFP_KERNEL);
	if (sd == NULL)
		return -ENOMEM;

	v4l2_i2c_subdev_init(sd, client, &cs3308_ops);

	/* Set some reasonable defaults */
	cs3308_write(sd, 0x0d, 0x00); /* Power up all channels */
	cs3308_write(sd, 0x0e, 0x00); /* Master Power */
	cs3308_write(sd, 0x0b, 0x00); /* Device Configuration */
	/* Set volume for each channel */
	for (i = 1; i <= 8; i++)
		cs3308_write(sd, i, 0xd2);
	cs3308_write(sd, 0x0a, 0x00); /* Unmute all channels */
	return 0;
}