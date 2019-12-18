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
struct TYPE_2__ {int base; int can_sleep; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  owner; int /*<<< orphan*/ * parent; int /*<<< orphan*/  label; } ;
struct mc9s08dz60 {TYPE_1__ chip; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_NUM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ *,TYPE_1__*,struct mc9s08dz60*) ; 
 struct mc9s08dz60* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mc9s08dz60*) ; 
 int /*<<< orphan*/  mc9s08dz60_direction_output ; 
 int /*<<< orphan*/  mc9s08dz60_get_value ; 
 int /*<<< orphan*/  mc9s08dz60_set_value ; 

__attribute__((used)) static int mc9s08dz60_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct mc9s08dz60 *mc9s;

	mc9s = devm_kzalloc(&client->dev, sizeof(*mc9s), GFP_KERNEL);
	if (!mc9s)
		return -ENOMEM;

	mc9s->chip.label = client->name;
	mc9s->chip.base = -1;
	mc9s->chip.parent = &client->dev;
	mc9s->chip.owner = THIS_MODULE;
	mc9s->chip.ngpio = GPIO_NUM;
	mc9s->chip.can_sleep = true;
	mc9s->chip.get = mc9s08dz60_get_value;
	mc9s->chip.set = mc9s08dz60_set_value;
	mc9s->chip.direction_output = mc9s08dz60_direction_output;
	mc9s->client = client;
	i2c_set_clientdata(client, mc9s);

	return devm_gpiochip_add_data(&client->dev, &mc9s->chip, mc9s);
}