#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct power_supply_config {struct bq24190_dev_info* drv_data; int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; int /*<<< orphan*/  of_node; int /*<<< orphan*/  attr_grp; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct bq24190_dev_info {int initialized; void* charger; void* battery; int /*<<< orphan*/  ss_reg; void* edev; int /*<<< orphan*/  input_current_limit_work; scalar_t__ f_reg; int /*<<< orphan*/  f_reg_lock; int /*<<< orphan*/  model_name; struct device* dev; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BQ24190_REG_SS_VBUS_STAT_MASK ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  bq24190_battery_desc ; 
 int /*<<< orphan*/  bq24190_charger_desc ; 
 int /*<<< orphan*/  bq24190_charger_supplied_to ; 
 int bq24190_configure_usb_otg (struct bq24190_dev_info*,int /*<<< orphan*/ ) ; 
 int bq24190_get_config (struct bq24190_dev_info*) ; 
 int bq24190_hw_init (struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  bq24190_input_current_limit_work ; 
 int /*<<< orphan*/  bq24190_irq_handler_thread ; 
 int bq24190_register_vbus_regulator (struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  bq24190_sysfs_groups ; 
 int /*<<< orphan*/  bq24190_sysfs_init_attrs () ; 
 int /*<<< orphan*/  bq24190_usb_extcon_cable ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_property_read_bool (struct device*,char*) ; 
 void* devm_extcon_dev_allocate (struct device*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (struct device*,void*) ; 
 struct bq24190_dev_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 void* power_supply_register (struct device*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (void*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq24190_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct device *dev = &client->dev;
	struct power_supply_config charger_cfg = {}, battery_cfg = {};
	struct bq24190_dev_info *bdi;
	int ret;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(dev, "No support for SMBUS_BYTE_DATA\n");
		return -ENODEV;
	}

	bdi = devm_kzalloc(dev, sizeof(*bdi), GFP_KERNEL);
	if (!bdi) {
		dev_err(dev, "Can't alloc bdi struct\n");
		return -ENOMEM;
	}

	bdi->client = client;
	bdi->dev = dev;
	strncpy(bdi->model_name, id->name, I2C_NAME_SIZE);
	mutex_init(&bdi->f_reg_lock);
	bdi->f_reg = 0;
	bdi->ss_reg = BQ24190_REG_SS_VBUS_STAT_MASK; /* impossible state */
	INIT_DELAYED_WORK(&bdi->input_current_limit_work,
			  bq24190_input_current_limit_work);

	i2c_set_clientdata(client, bdi);

	if (client->irq <= 0) {
		dev_err(dev, "Can't get irq info\n");
		return -EINVAL;
	}

	bdi->edev = devm_extcon_dev_allocate(dev, bq24190_usb_extcon_cable);
	if (IS_ERR(bdi->edev))
		return PTR_ERR(bdi->edev);

	ret = devm_extcon_dev_register(dev, bdi->edev);
	if (ret < 0)
		return ret;

	pm_runtime_enable(dev);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, 600);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		dev_err(dev, "pm_runtime_get failed: %i\n", ret);
		goto out_pmrt;
	}

#ifdef CONFIG_SYSFS
	bq24190_sysfs_init_attrs();
	charger_cfg.attr_grp = bq24190_sysfs_groups;
#endif

	charger_cfg.drv_data = bdi;
	charger_cfg.of_node = dev->of_node;
	charger_cfg.supplied_to = bq24190_charger_supplied_to;
	charger_cfg.num_supplicants = ARRAY_SIZE(bq24190_charger_supplied_to),
	bdi->charger = power_supply_register(dev, &bq24190_charger_desc,
						&charger_cfg);
	if (IS_ERR(bdi->charger)) {
		dev_err(dev, "Can't register charger\n");
		ret = PTR_ERR(bdi->charger);
		goto out_pmrt;
	}

	/* the battery class is deprecated and will be removed. */
	/* in the interim, this property hides it.              */
	if (!device_property_read_bool(dev, "omit-battery-class")) {
		battery_cfg.drv_data = bdi;
		bdi->battery = power_supply_register(dev, &bq24190_battery_desc,
						     &battery_cfg);
		if (IS_ERR(bdi->battery)) {
			dev_err(dev, "Can't register battery\n");
			ret = PTR_ERR(bdi->battery);
			goto out_charger;
		}
	}

	ret = bq24190_get_config(bdi);
	if (ret < 0) {
		dev_err(dev, "Can't get devicetree config\n");
		goto out_charger;
	}

	ret = bq24190_hw_init(bdi);
	if (ret < 0) {
		dev_err(dev, "Hardware init failed\n");
		goto out_charger;
	}

	ret = bq24190_configure_usb_otg(bdi, bdi->ss_reg);
	if (ret < 0)
		goto out_charger;

	bdi->initialized = true;

	ret = devm_request_threaded_irq(dev, client->irq, NULL,
			bq24190_irq_handler_thread,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"bq24190-charger", bdi);
	if (ret < 0) {
		dev_err(dev, "Can't set up irq handler\n");
		goto out_charger;
	}

	ret = bq24190_register_vbus_regulator(bdi);
	if (ret < 0)
		goto out_charger;

	enable_irq_wake(client->irq);

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return 0;

out_charger:
	if (!IS_ERR_OR_NULL(bdi->battery))
		power_supply_unregister(bdi->battery);
	power_supply_unregister(bdi->charger);

out_pmrt:
	pm_runtime_put_sync(dev);
	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);
	return ret;
}