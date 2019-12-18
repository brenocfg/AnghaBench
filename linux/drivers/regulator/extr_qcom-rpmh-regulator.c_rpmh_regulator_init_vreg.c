#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpmh_vreg_init_data {TYPE_1__* hw_data; int /*<<< orphan*/  supply_name; scalar_t__ name; int /*<<< orphan*/  resource_name; } ;
struct TYPE_7__ {int n_linear_ranges; int n_voltages; scalar_t__ fixed_uV; int /*<<< orphan*/  of_map_mode; int /*<<< orphan*/  ops; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; int /*<<< orphan*/ * linear_ranges; int /*<<< orphan*/  supply_name; scalar_t__ name; } ;
struct rpmh_vreg {int enabled; int /*<<< orphan*/  addr; TYPE_3__ rdesc; TYPE_1__* hw_data; int /*<<< orphan*/  always_wait_for_ack; int /*<<< orphan*/  mode; int /*<<< orphan*/  voltage_selector; struct device* dev; } ;
struct TYPE_6__ {scalar_t__ min_uV; scalar_t__ max_uV; } ;
struct regulator_init_data {TYPE_2__ constraints; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct rpmh_vreg* driver_data; struct device_node* of_node; struct regulator_init_data* init_data; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  rpmh_resource_name ;
struct TYPE_5__ {int n_voltages; scalar_t__ regulator_type; int /*<<< orphan*/  of_map_mode; int /*<<< orphan*/  ops; int /*<<< orphan*/  voltage_range; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENOTRECOVERABLE ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_MODE_INVALID ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ XOB ; 
 int /*<<< orphan*/  cmd_db_read_addr (char*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct device_node*,...) ; 
 struct regulator_dev* devm_regulator_register (struct device*,TYPE_3__*,struct regulator_config*) ; 
 struct regulator_init_data* of_get_regulator_init_data (struct device*,struct device_node*,TYPE_3__*) ; 
 scalar_t__ of_node_name_eq (struct device_node*,scalar_t__) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int rpmh_regulator_init_vreg(struct rpmh_vreg *vreg, struct device *dev,
			struct device_node *node, const char *pmic_id,
			const struct rpmh_vreg_init_data *pmic_rpmh_data)
{
	struct regulator_config reg_config = {};
	char rpmh_resource_name[20] = "";
	const struct rpmh_vreg_init_data *rpmh_data;
	struct regulator_init_data *init_data;
	struct regulator_dev *rdev;
	int ret;

	vreg->dev = dev;

	for (rpmh_data = pmic_rpmh_data; rpmh_data->name; rpmh_data++)
		if (of_node_name_eq(node, rpmh_data->name))
			break;

	if (!rpmh_data->name) {
		dev_err(dev, "Unknown regulator %pOFn\n", node);
		return -EINVAL;
	}

	scnprintf(rpmh_resource_name, sizeof(rpmh_resource_name),
		rpmh_data->resource_name, pmic_id);

	vreg->addr = cmd_db_read_addr(rpmh_resource_name);
	if (!vreg->addr) {
		dev_err(dev, "%pOFn: could not find RPMh address for resource %s\n",
			node, rpmh_resource_name);
		return -ENODEV;
	}

	vreg->rdesc.name = rpmh_data->name;
	vreg->rdesc.supply_name = rpmh_data->supply_name;
	vreg->hw_data = rpmh_data->hw_data;

	vreg->enabled = -EINVAL;
	vreg->voltage_selector = -ENOTRECOVERABLE;
	vreg->mode = REGULATOR_MODE_INVALID;

	if (rpmh_data->hw_data->n_voltages) {
		vreg->rdesc.linear_ranges = &rpmh_data->hw_data->voltage_range;
		vreg->rdesc.n_linear_ranges = 1;
		vreg->rdesc.n_voltages = rpmh_data->hw_data->n_voltages;
	}

	vreg->always_wait_for_ack = of_property_read_bool(node,
						"qcom,always-wait-for-ack");

	vreg->rdesc.owner	= THIS_MODULE;
	vreg->rdesc.type	= REGULATOR_VOLTAGE;
	vreg->rdesc.ops		= vreg->hw_data->ops;
	vreg->rdesc.of_map_mode	= vreg->hw_data->of_map_mode;

	init_data = of_get_regulator_init_data(dev, node, &vreg->rdesc);
	if (!init_data)
		return -ENOMEM;

	if (rpmh_data->hw_data->regulator_type == XOB &&
	    init_data->constraints.min_uV &&
	    init_data->constraints.min_uV == init_data->constraints.max_uV) {
		vreg->rdesc.fixed_uV = init_data->constraints.min_uV;
		vreg->rdesc.n_voltages = 1;
	}

	reg_config.dev		= dev;
	reg_config.init_data	= init_data;
	reg_config.of_node	= node;
	reg_config.driver_data	= vreg;

	rdev = devm_regulator_register(dev, &vreg->rdesc, &reg_config);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(dev, "%pOFn: devm_regulator_register() failed, ret=%d\n",
			node, ret);
		return ret;
	}

	dev_dbg(dev, "%pOFn regulator registered for RPMh resource %s @ 0x%05X\n",
		node, rpmh_resource_name, vreg->addr);

	return 0;
}