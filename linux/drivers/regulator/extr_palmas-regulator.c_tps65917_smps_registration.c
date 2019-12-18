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
struct regulator_dev {int dummy; } ;
struct regulator_desc {int n_linear_ranges; int id; int ramp_delay; unsigned int enable_mask; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  enable_val; void* enable_reg; int /*<<< orphan*/  vsel_mask; void* vsel_reg; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/ * ops; int /*<<< orphan*/  linear_ranges; int /*<<< orphan*/  name; } ;
struct regulator_config {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * init_data; } ;
struct palmas_regs_info {unsigned int vsel_addr; unsigned int ctrl_addr; int /*<<< orphan*/  sname; int /*<<< orphan*/  name; } ;
struct palmas_reg_init {scalar_t__ roof_floor; } ;
struct palmas_pmic_platform_data {int /*<<< orphan*/ ** reg_data; struct palmas_reg_init** reg_init; } ;
struct palmas_pmic_driver_data {int smps_start; int smps_end; TYPE_1__* palmas_matches; struct palmas_regs_info* palmas_regs_info; } ;
struct palmas_pmic {int* range; unsigned int* current_reg_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; scalar_t__ smps12; struct regulator_desc* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 void* PALMAS_BASE_TO_REG (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK ; 
 int /*<<< orphan*/  PALMAS_SMPS12_VOLTAGE_VSEL_MASK ; 
 int /*<<< orphan*/  PALMAS_SMPS_BASE ; 
 int /*<<< orphan*/  PALMAS_SMPS_NUM_VOLTAGES ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  SMPS_CTRL_MODE_ON ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int TPS65917_REG_SMPS1 ; 
 int TPS65917_REG_SMPS2 ; 
 unsigned int TPS65917_SMPS1_VOLTAGE_RANGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ ,struct regulator_desc*,struct regulator_config*) ; 
 int palmas_smps_init (int /*<<< orphan*/ ,int,struct palmas_reg_init*) ; 
 int palmas_smps_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  smps_high_ranges ; 
 int /*<<< orphan*/  smps_low_ranges ; 
 int /*<<< orphan*/  tps65917_ops_ext_control_smps ; 
 int /*<<< orphan*/  tps65917_ops_smps ; 

__attribute__((used)) static int tps65917_smps_registration(struct palmas_pmic *pmic,
				      struct palmas_pmic_driver_data *ddata,
				      struct palmas_pmic_platform_data *pdata,
				      const char *pdev_name,
				      struct regulator_config config)
{
	int id, ret;
	unsigned int addr, reg;
	struct regulator_dev *rdev;
	struct palmas_reg_init *reg_init;
	struct palmas_regs_info *rinfo;
	struct regulator_desc *desc;

	for (id = ddata->smps_start; id <= ddata->smps_end; id++) {
		/*
		 * Miss out regulators which are not available due
		 * to slaving configurations.
		 */
		desc = &pmic->desc[id];
		desc->n_linear_ranges = 3;
		if ((id == TPS65917_REG_SMPS2 || id == TPS65917_REG_SMPS1) &&
		    pmic->smps12)
			continue;

		/* Initialise sleep/init values from platform data */
		if (pdata && pdata->reg_init[id]) {
			reg_init = pdata->reg_init[id];
			ret = palmas_smps_init(pmic->palmas, id, reg_init);
			if (ret)
				return ret;
		} else {
			reg_init = NULL;
		}
		rinfo = &ddata->palmas_regs_info[id];

		/* Register the regulators */
		desc->name = rinfo->name;
		desc->id = id;

		/*
		 * Read and store the RANGE bit for later use
		 * This must be done before regulator is probed,
		 * otherwise we error in probe with unsupportable
		 * ranges. Read the current smps mode for later use.
		 */
		addr = rinfo->vsel_addr;

		ret = palmas_smps_read(pmic->palmas, addr, &reg);
		if (ret)
			return ret;
		if (reg & TPS65917_SMPS1_VOLTAGE_RANGE)
			pmic->range[id] = 1;

		if (pmic->range[id])
			desc->linear_ranges = smps_high_ranges;
		else
			desc->linear_ranges = smps_low_ranges;

		if (reg_init && reg_init->roof_floor)
			desc->ops = &tps65917_ops_ext_control_smps;
		else
			desc->ops = &tps65917_ops_smps;
		desc->n_voltages = PALMAS_SMPS_NUM_VOLTAGES;
		desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
						    rinfo->vsel_addr);
		desc->vsel_mask = PALMAS_SMPS12_VOLTAGE_VSEL_MASK;
		desc->ramp_delay = 2500;

		/* Read the smps mode for later use. */
		addr = rinfo->ctrl_addr;
		ret = palmas_smps_read(pmic->palmas, addr, &reg);
		if (ret)
			return ret;
		pmic->current_reg_mode[id] = reg &
				PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
		desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
						      rinfo->ctrl_addr);
		desc->enable_mask = PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
		/* set_mode overrides this value */
		desc->enable_val = SMPS_CTRL_MODE_ON;

		desc->type = REGULATOR_VOLTAGE;
		desc->owner = THIS_MODULE;

		if (pdata)
			config.init_data = pdata->reg_data[id];
		else
			config.init_data = NULL;

		desc->supply_name = rinfo->sname;
		config.of_node = ddata->palmas_matches[id].of_node;

		rdev = devm_regulator_register(pmic->dev, desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(pmic->dev,
				"failed to register %s regulator\n",
				pdev_name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}