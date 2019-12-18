#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct power_supply_desc {int /*<<< orphan*/  external_power_changed; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct power_supply_config {struct bq27xxx_device_info* drv_data; int /*<<< orphan*/  of_node; } ;
struct bq27xxx_device_info {size_t chip; int /*<<< orphan*/  list; int /*<<< orphan*/  bat; TYPE_1__* dev; int /*<<< orphan*/  name; int /*<<< orphan*/  opts; int /*<<< orphan*/  dm_regs; int /*<<< orphan*/  unseal_key; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;
struct TYPE_6__ {int /*<<< orphan*/  props_size; int /*<<< orphan*/  props; int /*<<< orphan*/  opts; int /*<<< orphan*/  dm_regs; int /*<<< orphan*/  unseal_key; int /*<<< orphan*/  regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq27xxx_battery_devices ; 
 int /*<<< orphan*/  bq27xxx_battery_get_property ; 
 int /*<<< orphan*/  bq27xxx_battery_poll ; 
 int /*<<< orphan*/  bq27xxx_battery_settings (struct bq27xxx_device_info*) ; 
 int /*<<< orphan*/  bq27xxx_battery_update (struct bq27xxx_device_info*) ; 
 TYPE_4__* bq27xxx_chip_data ; 
 int /*<<< orphan*/  bq27xxx_external_power_changed ; 
 int /*<<< orphan*/  bq27xxx_list_lock ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct power_supply_desc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_register_no_ws (TYPE_1__*,struct power_supply_desc*,struct power_supply_config*) ; 

int bq27xxx_battery_setup(struct bq27xxx_device_info *di)
{
	struct power_supply_desc *psy_desc;
	struct power_supply_config psy_cfg = {
		.of_node = di->dev->of_node,
		.drv_data = di,
	};

	INIT_DELAYED_WORK(&di->work, bq27xxx_battery_poll);
	mutex_init(&di->lock);

	di->regs       = bq27xxx_chip_data[di->chip].regs;
	di->unseal_key = bq27xxx_chip_data[di->chip].unseal_key;
	di->dm_regs    = bq27xxx_chip_data[di->chip].dm_regs;
	di->opts       = bq27xxx_chip_data[di->chip].opts;

	psy_desc = devm_kzalloc(di->dev, sizeof(*psy_desc), GFP_KERNEL);
	if (!psy_desc)
		return -ENOMEM;

	psy_desc->name = di->name;
	psy_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	psy_desc->properties = bq27xxx_chip_data[di->chip].props;
	psy_desc->num_properties = bq27xxx_chip_data[di->chip].props_size;
	psy_desc->get_property = bq27xxx_battery_get_property;
	psy_desc->external_power_changed = bq27xxx_external_power_changed;

	di->bat = power_supply_register_no_ws(di->dev, psy_desc, &psy_cfg);
	if (IS_ERR(di->bat)) {
		dev_err(di->dev, "failed to register battery\n");
		return PTR_ERR(di->bat);
	}

	bq27xxx_battery_settings(di);
	bq27xxx_battery_update(di);

	mutex_lock(&bq27xxx_list_lock);
	list_add(&di->list, &bq27xxx_battery_devices);
	mutex_unlock(&bq27xxx_list_lock);

	return 0;
}