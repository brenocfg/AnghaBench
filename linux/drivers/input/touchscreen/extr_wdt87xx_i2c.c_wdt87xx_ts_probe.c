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
struct wdt87xx_data {int /*<<< orphan*/  param; int /*<<< orphan*/  phys; int /*<<< orphan*/  fw_mutex; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; TYPE_1__* adapter; } ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_device_add_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wdt87xx_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wdt87xx_data*) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wdt87xx_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  wdt87xx_attr_group ; 
 int wdt87xx_get_sysparam (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int wdt87xx_ts_create_input_device (struct wdt87xx_data*) ; 
 int /*<<< orphan*/  wdt87xx_ts_interrupt ; 

__attribute__((used)) static int wdt87xx_ts_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct wdt87xx_data *wdt;
	int error;

	dev_dbg(&client->dev, "adapter=%d, client irq: %d\n",
		client->adapter->nr, client->irq);

	/* Check if the I2C function is ok in this adaptor */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENXIO;

	wdt = devm_kzalloc(&client->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->client = client;
	mutex_init(&wdt->fw_mutex);
	i2c_set_clientdata(client, wdt);

	snprintf(wdt->phys, sizeof(wdt->phys), "i2c-%u-%04x/input0",
		 client->adapter->nr, client->addr);

	error = wdt87xx_get_sysparam(client, &wdt->param);
	if (error)
		return error;

	error = wdt87xx_ts_create_input_device(wdt);
	if (error)
		return error;

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, wdt87xx_ts_interrupt,
					  IRQF_ONESHOT,
					  client->name, wdt);
	if (error) {
		dev_err(&client->dev, "request irq failed: %d\n", error);
		return error;
	}

	error = devm_device_add_group(&client->dev, &wdt87xx_attr_group);
	if (error) {
		dev_err(&client->dev, "create sysfs failed: %d\n", error);
		return error;
	}

	return 0;
}