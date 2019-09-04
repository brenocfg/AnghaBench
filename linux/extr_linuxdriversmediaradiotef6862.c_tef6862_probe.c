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
struct tef6862_state {struct v4l2_subdev sd; int /*<<< orphan*/  freq; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  TEF6862_LO_FREQ ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct tef6862_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tef6862_ops ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tef6862_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct tef6862_state *state;
	struct v4l2_subdev *sd;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = kzalloc(sizeof(struct tef6862_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;
	state->freq = TEF6862_LO_FREQ;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tef6862_ops);

	return 0;
}