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
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_1__* adapter; } ;
struct bt856 {int norm; struct v4l2_subdev sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int V4L2_STD_NTSC ; 
 int /*<<< orphan*/  bt856_dump (struct bt856*) ; 
 int /*<<< orphan*/  bt856_ops ; 
 int /*<<< orphan*/  bt856_setbit (struct bt856*,int,int,int) ; 
 int /*<<< orphan*/  bt856_write (struct bt856*,int,int) ; 
 scalar_t__ debug ; 
 struct bt856* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bt856_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct bt856 *encoder;
	struct v4l2_subdev *sd;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	encoder = devm_kzalloc(&client->dev, sizeof(*encoder), GFP_KERNEL);
	if (encoder == NULL)
		return -ENOMEM;
	sd = &encoder->sd;
	v4l2_i2c_subdev_init(sd, client, &bt856_ops);
	encoder->norm = V4L2_STD_NTSC;

	bt856_write(encoder, 0xdc, 0x18);
	bt856_write(encoder, 0xda, 0);
	bt856_write(encoder, 0xde, 0);

	bt856_setbit(encoder, 0xdc, 3, 1);
	/*bt856_setbit(encoder, 0xdc, 6, 0);*/
	bt856_setbit(encoder, 0xdc, 4, 1);

	if (encoder->norm & V4L2_STD_NTSC)
		bt856_setbit(encoder, 0xdc, 2, 0);
	else
		bt856_setbit(encoder, 0xdc, 2, 1);

	bt856_setbit(encoder, 0xdc, 1, 1);
	bt856_setbit(encoder, 0xde, 4, 0);
	bt856_setbit(encoder, 0xde, 3, 1);

	if (debug != 0)
		bt856_dump(encoder);
	return 0;
}