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
struct i2c_client {int addr; int /*<<< orphan*/  adapter; } ;
struct adv76xx_platform_data {scalar_t__* i2c_addresses; } ;
struct adv76xx_state {struct adv76xx_platform_data pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct i2c_client*) ; 
 TYPE_1__* adv76xx_default_addresses ; 
 struct i2c_client* i2c_new_ancillary_device (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_dummy_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,unsigned int,int) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static struct i2c_client *adv76xx_dummy_client(struct v4l2_subdev *sd,
					       unsigned int page)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct adv76xx_state *state = to_state(sd);
	struct adv76xx_platform_data *pdata = &state->pdata;
	unsigned int io_reg = 0xf2 + page;
	struct i2c_client *new_client;

	if (pdata && pdata->i2c_addresses[page])
		new_client = i2c_new_dummy_device(client->adapter,
					   pdata->i2c_addresses[page]);
	else
		new_client = i2c_new_ancillary_device(client,
				adv76xx_default_addresses[page].name,
				adv76xx_default_addresses[page].default_addr);

	if (!IS_ERR(new_client))
		io_write(sd, io_reg, new_client->addr << 1);

	return new_client;
}