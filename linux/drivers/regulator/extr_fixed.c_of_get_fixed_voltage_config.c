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
struct TYPE_2__ {scalar_t__ min_uV; scalar_t__ max_uV; scalar_t__ boot_on; int /*<<< orphan*/  name; scalar_t__ apply_uV; } ;
struct regulator_init_data {TYPE_1__ constraints; } ;
struct regulator_desc {int dummy; } ;
struct fixed_voltage_config {scalar_t__ microvolts; int enabled_at_boot; char* input_supply; int /*<<< orphan*/  startup_delay; int /*<<< orphan*/  supply_name; struct regulator_init_data* init_data; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct fixed_voltage_config* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct fixed_voltage_config* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct regulator_init_data* of_get_regulator_init_data (struct device*,struct device_node*,struct regulator_desc const*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fixed_voltage_config *
of_get_fixed_voltage_config(struct device *dev,
			    const struct regulator_desc *desc)
{
	struct fixed_voltage_config *config;
	struct device_node *np = dev->of_node;
	struct regulator_init_data *init_data;

	config = devm_kzalloc(dev, sizeof(struct fixed_voltage_config),
								 GFP_KERNEL);
	if (!config)
		return ERR_PTR(-ENOMEM);

	config->init_data = of_get_regulator_init_data(dev, dev->of_node, desc);
	if (!config->init_data)
		return ERR_PTR(-EINVAL);

	init_data = config->init_data;
	init_data->constraints.apply_uV = 0;

	config->supply_name = init_data->constraints.name;
	if (init_data->constraints.min_uV == init_data->constraints.max_uV) {
		config->microvolts = init_data->constraints.min_uV;
	} else {
		dev_err(dev,
			 "Fixed regulator specified with variable voltages\n");
		return ERR_PTR(-EINVAL);
	}

	if (init_data->constraints.boot_on)
		config->enabled_at_boot = true;

	of_property_read_u32(np, "startup-delay-us", &config->startup_delay);

	if (of_find_property(np, "vin-supply", NULL))
		config->input_supply = "vin";

	return config;
}