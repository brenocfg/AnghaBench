#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct ths7303_state {struct v4l2_subdev sd; struct ths7303_platform_data* pdata; } ;
struct ths7303_platform_data {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {struct ths7303_platform_data* platform_data; } ;
struct i2c_client {int addr; TYPE_2__ dev; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  THS7303_FILTER_MODE_480I_576I ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct ths7303_state* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ths7303_ops ; 
 scalar_t__ ths7303_setval (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ths7303_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ths7303_platform_data *pdata = client->dev.platform_data;
	struct ths7303_state *state;
	struct v4l2_subdev *sd;

	if (pdata == NULL) {
		dev_err(&client->dev, "No platform data\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, sizeof(struct ths7303_state),
			     GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	state->pdata = pdata;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &ths7303_ops);

	/* set to default 480I_576I filter mode */
	if (ths7303_setval(sd, THS7303_FILTER_MODE_480I_576I) < 0) {
		v4l_err(client, "Setting to 480I_576I filter mode failed!\n");
		return -EINVAL;
	}

	return 0;
}