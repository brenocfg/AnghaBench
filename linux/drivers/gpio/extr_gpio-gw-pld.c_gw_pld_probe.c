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
struct i2c_device_id {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct i2c_client {int /*<<< orphan*/  flags; struct device dev; } ;
struct TYPE_2__ {int base; int can_sleep; int ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; struct device_node* of_node; struct device* parent; } ;
struct gw_pld {int out; TYPE_1__ chip; struct i2c_client* client; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_IGNORE_NAK ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct gw_pld*) ; 
 struct gw_pld* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gw_pld_get8 ; 
 int /*<<< orphan*/  gw_pld_input8 ; 
 int /*<<< orphan*/  gw_pld_output8 ; 
 int /*<<< orphan*/  gw_pld_set8 ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct gw_pld*) ; 

__attribute__((used)) static int gw_pld_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device_node *np = dev->of_node;
	struct gw_pld *gw;
	int ret;

	gw = devm_kzalloc(dev, sizeof(*gw), GFP_KERNEL);
	if (!gw)
		return -ENOMEM;

	gw->chip.base = -1;
	gw->chip.can_sleep = true;
	gw->chip.parent = dev;
	gw->chip.of_node = np;
	gw->chip.owner = THIS_MODULE;
	gw->chip.label = dev_name(dev);
	gw->chip.ngpio = 8;
	gw->chip.direction_input = gw_pld_input8;
	gw->chip.get = gw_pld_get8;
	gw->chip.direction_output = gw_pld_output8;
	gw->chip.set = gw_pld_set8;
	gw->client = client;

	/*
	 * The Gateworks I2C PLD chip does not properly send the acknowledge
	 * bit at all times, but we can still use the standard i2c_smbus
	 * functions by simply ignoring this bit.
	 */
	client->flags |= I2C_M_IGNORE_NAK;
	gw->out = 0xFF;

	i2c_set_clientdata(client, gw);

	ret = devm_gpiochip_add_data(dev, &gw->chip, gw);
	if (ret)
		return ret;

	dev_info(dev, "registered Gateworks PLD GPIO device\n");

	return 0;
}