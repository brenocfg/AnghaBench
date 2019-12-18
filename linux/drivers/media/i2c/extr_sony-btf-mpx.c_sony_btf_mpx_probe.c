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
struct sony_btf_mpx {int /*<<< orphan*/  audmode; scalar_t__ mpxmode; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 struct sony_btf_mpx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sony_btf_mpx_ops ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sony_btf_mpx_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct sony_btf_mpx *t;
	struct v4l2_subdev *sd;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	t = devm_kzalloc(&client->dev, sizeof(*t), GFP_KERNEL);
	if (t == NULL)
		return -ENOMEM;

	sd = &t->sd;
	v4l2_i2c_subdev_init(sd, client, &sony_btf_mpx_ops);

	/* Initialize sony_btf_mpx */
	t->mpxmode = 0;
	t->audmode = V4L2_TUNER_MODE_STEREO;

	return 0;
}