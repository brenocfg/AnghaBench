#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct rmi_device_platform_data {int /*<<< orphan*/  irq; } ;
struct TYPE_13__ {char* proto_name; int /*<<< orphan*/ * ops; TYPE_2__* dev; struct rmi_device_platform_data pdata; } ;
struct rmi_i2c_xport {TYPE_1__ xport; int /*<<< orphan*/  page_mutex; struct i2c_client* client; int /*<<< orphan*/  startup_delay; TYPE_3__* supplies; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; } ;
struct TYPE_15__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  RMI_DEBUG_XPORT ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct rmi_device_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int devm_add_action_or_reset (TYPE_2__*,int /*<<< orphan*/ ,struct rmi_i2c_xport*) ; 
 struct rmi_i2c_xport* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rmi_i2c_xport*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  rmi_dbg (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmi_i2c_ops ; 
 int /*<<< orphan*/  rmi_i2c_regulator_bulk_disable ; 
 int /*<<< orphan*/  rmi_i2c_unregister_transport ; 
 int rmi_register_transport_device (TYPE_1__*) ; 
 int rmi_set_page (struct rmi_i2c_xport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_i2c_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct rmi_device_platform_data *pdata;
	struct rmi_device_platform_data *client_pdata =
					dev_get_platdata(&client->dev);
	struct rmi_i2c_xport *rmi_i2c;
	int error;

	rmi_i2c = devm_kzalloc(&client->dev, sizeof(struct rmi_i2c_xport),
				GFP_KERNEL);
	if (!rmi_i2c)
		return -ENOMEM;

	pdata = &rmi_i2c->xport.pdata;

	if (!client->dev.of_node && client_pdata)
		*pdata = *client_pdata;

	pdata->irq = client->irq;

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev, "Probing %s.\n",
			dev_name(&client->dev));

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev,
			"adapter does not support required functionality\n");
		return -ENODEV;
	}

	rmi_i2c->supplies[0].supply = "vdd";
	rmi_i2c->supplies[1].supply = "vio";
	error = devm_regulator_bulk_get(&client->dev,
					 ARRAY_SIZE(rmi_i2c->supplies),
					 rmi_i2c->supplies);
	if (error < 0)
		return error;

	error = regulator_bulk_enable(ARRAY_SIZE(rmi_i2c->supplies),
				       rmi_i2c->supplies);
	if (error < 0)
		return error;

	error = devm_add_action_or_reset(&client->dev,
					  rmi_i2c_regulator_bulk_disable,
					  rmi_i2c);
	if (error)
		return error;

	of_property_read_u32(client->dev.of_node, "syna,startup-delay-ms",
			     &rmi_i2c->startup_delay);

	msleep(rmi_i2c->startup_delay);

	rmi_i2c->client = client;
	mutex_init(&rmi_i2c->page_mutex);

	rmi_i2c->xport.dev = &client->dev;
	rmi_i2c->xport.proto_name = "i2c";
	rmi_i2c->xport.ops = &rmi_i2c_ops;

	i2c_set_clientdata(client, rmi_i2c);

	/*
	 * Setting the page to zero will (a) make sure the PSR is in a
	 * known state, and (b) make sure we can talk to the device.
	 */
	error = rmi_set_page(rmi_i2c, 0);
	if (error) {
		dev_err(&client->dev, "Failed to set page select to 0\n");
		return error;
	}

	dev_info(&client->dev, "registering I2C-connected sensor\n");

	error = rmi_register_transport_device(&rmi_i2c->xport);
	if (error) {
		dev_err(&client->dev, "failed to register sensor: %d\n", error);
		return error;
	}

	error = devm_add_action_or_reset(&client->dev,
					  rmi_i2c_unregister_transport,
					  rmi_i2c);
	if (error)
		return error;

	return 0;
}