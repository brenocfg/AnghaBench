#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {TYPE_1__* driver; struct bq2415x_platform_data* platform_data; struct device_node* of_node; } ;
struct i2c_client {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct bq2415x_platform_data {int dummy; } ;
struct TYPE_12__ {scalar_t__ notify_device; int /*<<< orphan*/  resistor_sense; int /*<<< orphan*/  termination_current; int /*<<< orphan*/  charge_current; int /*<<< orphan*/  battery_regulation_voltage; int /*<<< orphan*/  weak_battery_voltage; int /*<<< orphan*/  current_limit; } ;
struct TYPE_11__ {scalar_t__ notifier_call; } ;
struct bq2415x_device {int id; char* name; int automode; scalar_t__ notify_node; TYPE_4__* dev; int /*<<< orphan*/  work; void* reported_mode; TYPE_3__ init_data; TYPE_2__ nb; scalar_t__ autotimer; void* mode; int /*<<< orphan*/  chip; } ;
struct acpi_device_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (TYPE_4__*) ; 
 void* BQ2415X_MODE_OFF ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct power_supply*) ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_CURRENT_MAX ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  bq2415x_id ; 
 int /*<<< orphan*/  bq2415x_id_mutex ; 
 scalar_t__ bq2415x_notifier_call ; 
 int /*<<< orphan*/  bq2415x_power_supply_exit (struct bq2415x_device*) ; 
 int bq2415x_power_supply_init (struct bq2415x_device*) ; 
 int /*<<< orphan*/  bq2415x_reset_chip (struct bq2415x_device*) ; 
 int /*<<< orphan*/  bq2415x_set_autotimer (struct bq2415x_device*,int) ; 
 int bq2415x_set_defaults (struct bq2415x_device*) ; 
 int /*<<< orphan*/  bq2415x_set_mode (struct bq2415x_device*,void*) ; 
 int /*<<< orphan*/  bq2415x_timer_work ; 
 int /*<<< orphan*/  bq2415x_update_reported_mode (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 int device_property_read_u32 (TYPE_4__*,char*,int /*<<< orphan*/ *) ; 
 struct bq2415x_device* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bq2415x_device*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct bq2415x_platform_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 
 scalar_t__ of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct power_supply* power_supply_get_by_name (scalar_t__) ; 
 struct power_supply* power_supply_get_by_phandle (struct device_node*,char*) ; 
 int power_supply_get_property (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 
 int /*<<< orphan*/  power_supply_put (struct power_supply*) ; 
 int power_supply_reg_notifier (TYPE_2__*) ; 

__attribute__((used)) static int bq2415x_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int ret;
	int num;
	char *name = NULL;
	struct bq2415x_device *bq;
	struct device_node *np = client->dev.of_node;
	struct bq2415x_platform_data *pdata = client->dev.platform_data;
	const struct acpi_device_id *acpi_id = NULL;
	struct power_supply *notify_psy = NULL;
	union power_supply_propval prop;

	if (!np && !pdata && !ACPI_HANDLE(&client->dev)) {
		dev_err(&client->dev, "Neither devicetree, nor platform data, nor ACPI support\n");
		return -ENODEV;
	}

	/* Get new ID for the new device */
	mutex_lock(&bq2415x_id_mutex);
	num = idr_alloc(&bq2415x_id, client, 0, 0, GFP_KERNEL);
	mutex_unlock(&bq2415x_id_mutex);
	if (num < 0)
		return num;

	if (id) {
		name = kasprintf(GFP_KERNEL, "%s-%d", id->name, num);
	} else if (ACPI_HANDLE(&client->dev)) {
		acpi_id =
			acpi_match_device(client->dev.driver->acpi_match_table,
					  &client->dev);
		if (!acpi_id) {
			dev_err(&client->dev, "failed to match device name\n");
			ret = -ENODEV;
			goto error_1;
		}
		name = kasprintf(GFP_KERNEL, "%s-%d", acpi_id->id, num);
	}
	if (!name) {
		dev_err(&client->dev, "failed to allocate device name\n");
		ret = -ENOMEM;
		goto error_1;
	}

	bq = devm_kzalloc(&client->dev, sizeof(*bq), GFP_KERNEL);
	if (!bq) {
		ret = -ENOMEM;
		goto error_2;
	}

	i2c_set_clientdata(client, bq);

	bq->id = num;
	bq->dev = &client->dev;
	if (id)
		bq->chip = id->driver_data;
	else if (ACPI_HANDLE(bq->dev))
		bq->chip = acpi_id->driver_data;
	bq->name = name;
	bq->mode = BQ2415X_MODE_OFF;
	bq->reported_mode = BQ2415X_MODE_OFF;
	bq->autotimer = 0;
	bq->automode = 0;

	if (np || ACPI_HANDLE(bq->dev)) {
		ret = device_property_read_u32(bq->dev,
					       "ti,current-limit",
					       &bq->init_data.current_limit);
		if (ret)
			goto error_2;
		ret = device_property_read_u32(bq->dev,
					"ti,weak-battery-voltage",
					&bq->init_data.weak_battery_voltage);
		if (ret)
			goto error_2;
		ret = device_property_read_u32(bq->dev,
				"ti,battery-regulation-voltage",
				&bq->init_data.battery_regulation_voltage);
		if (ret)
			goto error_2;
		ret = device_property_read_u32(bq->dev,
					       "ti,charge-current",
					       &bq->init_data.charge_current);
		if (ret)
			goto error_2;
		ret = device_property_read_u32(bq->dev,
				"ti,termination-current",
				&bq->init_data.termination_current);
		if (ret)
			goto error_2;
		ret = device_property_read_u32(bq->dev,
					       "ti,resistor-sense",
					       &bq->init_data.resistor_sense);
		if (ret)
			goto error_2;
		if (np)
			bq->notify_node = of_parse_phandle(np,
						"ti,usb-charger-detection", 0);
	} else {
		memcpy(&bq->init_data, pdata, sizeof(bq->init_data));
	}

	bq2415x_reset_chip(bq);

	ret = bq2415x_power_supply_init(bq);
	if (ret) {
		dev_err(bq->dev, "failed to register power supply: %d\n", ret);
		goto error_2;
	}

	ret = bq2415x_set_defaults(bq);
	if (ret) {
		dev_err(bq->dev, "failed to set default values: %d\n", ret);
		goto error_3;
	}

	if (bq->notify_node || bq->init_data.notify_device) {
		bq->nb.notifier_call = bq2415x_notifier_call;
		ret = power_supply_reg_notifier(&bq->nb);
		if (ret) {
			dev_err(bq->dev, "failed to reg notifier: %d\n", ret);
			goto error_3;
		}

		bq->automode = 1;
		dev_info(bq->dev, "automode supported, waiting for events\n");
	} else {
		bq->automode = -1;
		dev_info(bq->dev, "automode not supported\n");
	}

	/* Query for initial reported_mode and set it */
	if (bq->nb.notifier_call) {
		if (np) {
			notify_psy = power_supply_get_by_phandle(np,
						"ti,usb-charger-detection");
			if (IS_ERR(notify_psy))
				notify_psy = NULL;
		} else if (bq->init_data.notify_device) {
			notify_psy = power_supply_get_by_name(
						bq->init_data.notify_device);
		}
	}
	if (notify_psy) {
		ret = power_supply_get_property(notify_psy,
					POWER_SUPPLY_PROP_CURRENT_MAX, &prop);
		power_supply_put(notify_psy);

		if (ret == 0) {
			bq2415x_update_reported_mode(bq, prop.intval);
			bq2415x_set_mode(bq, bq->reported_mode);
		}
	}

	INIT_DELAYED_WORK(&bq->work, bq2415x_timer_work);
	bq2415x_set_autotimer(bq, 1);

	dev_info(bq->dev, "driver registered\n");
	return 0;

error_3:
	bq2415x_power_supply_exit(bq);
error_2:
	if (bq)
		of_node_put(bq->notify_node);
	kfree(name);
error_1:
	mutex_lock(&bq2415x_id_mutex);
	idr_remove(&bq2415x_id, num);
	mutex_unlock(&bq2415x_id_mutex);

	return ret;
}