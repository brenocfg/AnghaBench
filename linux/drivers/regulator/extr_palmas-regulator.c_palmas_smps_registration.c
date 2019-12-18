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
struct regulator_desc {int id; unsigned int enable_mask; int min_uV; int uV_step; int n_linear_ranges; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  enable_val; void* enable_reg; int /*<<< orphan*/  vsel_mask; void* vsel_reg; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/ * ops; int /*<<< orphan*/  linear_ranges; void* bypass_mask; void* bypass_val_on; void* bypass_reg; int /*<<< orphan*/  name; int /*<<< orphan*/  ramp_delay; } ;
struct regulator_config {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * init_data; } ;
struct palmas_regs_info {unsigned int tstep_addr; unsigned int vsel_addr; unsigned int ctrl_addr; int /*<<< orphan*/  sname; int /*<<< orphan*/  name; } ;
struct palmas_reg_init {int /*<<< orphan*/  roof_floor; } ;
struct palmas_pmic_platform_data {int /*<<< orphan*/ ** reg_data; struct palmas_reg_init** reg_init; } ;
struct palmas_pmic_driver_data {int smps_start; int smps_end; TYPE_1__* palmas_matches; struct palmas_regs_info* palmas_regs_info; } ;
struct palmas_pmic {int* range; unsigned int* current_reg_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; int /*<<< orphan*/ * ramp_delay; struct regulator_desc* desc; int /*<<< orphan*/  smps457; int /*<<< orphan*/  smps123; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 void* PALMAS_BASE_TO_REG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PALMAS_PMIC_HAS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PALMAS_REG_SMPS10_OUT1 135 
#define  PALMAS_REG_SMPS10_OUT2 134 
#define  PALMAS_REG_SMPS12 133 
#define  PALMAS_REG_SMPS123 132 
#define  PALMAS_REG_SMPS3 131 
#define  PALMAS_REG_SMPS45 130 
#define  PALMAS_REG_SMPS457 129 
 int PALMAS_REG_SMPS6 ; 
#define  PALMAS_REG_SMPS7 128 
 int PALMAS_REG_SMPS8 ; 
 unsigned int PALMAS_SMPS10_CTRL ; 
 int /*<<< orphan*/  PALMAS_SMPS10_NUM_VOLTAGES ; 
 unsigned int PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK ; 
 unsigned int PALMAS_SMPS12_VOLTAGE_RANGE ; 
 int /*<<< orphan*/  PALMAS_SMPS12_VOLTAGE_VSEL_MASK ; 
 int /*<<< orphan*/  PALMAS_SMPS_BASE ; 
 int /*<<< orphan*/  PALMAS_SMPS_NUM_VOLTAGES ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  SMPS10_BOOST ; 
 unsigned int SMPS10_BOOST_EN ; 
 void* SMPS10_BYPASS_EN ; 
 unsigned int SMPS10_SWITCH_EN ; 
 int /*<<< orphan*/  SMPS10_VSEL ; 
 int /*<<< orphan*/  SMPS_CTRL_MODE_ON ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ ,struct regulator_desc*,struct regulator_config*) ; 
 int /*<<< orphan*/  palmas_ops_ext_control_smps ; 
 int /*<<< orphan*/  palmas_ops_smps ; 
 int /*<<< orphan*/  palmas_ops_smps10 ; 
 int palmas_smps_init (int /*<<< orphan*/ ,int,struct palmas_reg_init*) ; 
 int /*<<< orphan*/ * palmas_smps_ramp_delay ; 
 int palmas_smps_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  smps_high_ranges ; 
 int /*<<< orphan*/  smps_low_ranges ; 

__attribute__((used)) static int palmas_smps_registration(struct palmas_pmic *pmic,
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
		bool ramp_delay_support = false;

		/*
		 * Miss out regulators which are not available due
		 * to slaving configurations.
		 */
		switch (id) {
		case PALMAS_REG_SMPS12:
		case PALMAS_REG_SMPS3:
			if (pmic->smps123)
				continue;
			if (id == PALMAS_REG_SMPS12)
				ramp_delay_support = true;
			break;
		case PALMAS_REG_SMPS123:
			if (!pmic->smps123)
				continue;
			ramp_delay_support = true;
			break;
		case PALMAS_REG_SMPS45:
		case PALMAS_REG_SMPS7:
			if (pmic->smps457)
				continue;
			if (id == PALMAS_REG_SMPS45)
				ramp_delay_support = true;
			break;
		case PALMAS_REG_SMPS457:
			if (!pmic->smps457)
				continue;
			ramp_delay_support = true;
			break;
		case PALMAS_REG_SMPS10_OUT1:
		case PALMAS_REG_SMPS10_OUT2:
			if (!PALMAS_PMIC_HAS(pmic->palmas, SMPS10_BOOST))
				continue;
		}
		rinfo = &ddata->palmas_regs_info[id];
		desc = &pmic->desc[id];

		if ((id == PALMAS_REG_SMPS6) || (id == PALMAS_REG_SMPS8))
			ramp_delay_support = true;

		if (ramp_delay_support) {
			addr = rinfo->tstep_addr;
			ret = palmas_smps_read(pmic->palmas, addr, &reg);
			if (ret < 0) {
				dev_err(pmic->dev,
					"reading TSTEP reg failed: %d\n", ret);
				return ret;
			}
			desc->ramp_delay = palmas_smps_ramp_delay[reg & 0x3];
			pmic->ramp_delay[id] = desc->ramp_delay;
		}

		/* Initialise sleep/init values from platform data */
		if (pdata && pdata->reg_init[id]) {
			reg_init = pdata->reg_init[id];
			ret = palmas_smps_init(pmic->palmas, id, reg_init);
			if (ret)
				return ret;
		} else {
			reg_init = NULL;
		}

		/* Register the regulators */
		desc->name = rinfo->name;
		desc->id = id;

		switch (id) {
		case PALMAS_REG_SMPS10_OUT1:
		case PALMAS_REG_SMPS10_OUT2:
			desc->n_voltages = PALMAS_SMPS10_NUM_VOLTAGES;
			desc->ops = &palmas_ops_smps10;
			desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    PALMAS_SMPS10_CTRL);
			desc->vsel_mask = SMPS10_VSEL;
			desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    PALMAS_SMPS10_CTRL);
			if (id == PALMAS_REG_SMPS10_OUT1)
				desc->enable_mask = SMPS10_SWITCH_EN;
			else
				desc->enable_mask = SMPS10_BOOST_EN;
			desc->bypass_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    PALMAS_SMPS10_CTRL);
			desc->bypass_val_on = SMPS10_BYPASS_EN;
			desc->bypass_mask = SMPS10_BYPASS_EN;
			desc->min_uV = 3750000;
			desc->uV_step = 1250000;
			break;
		default:
			/*
			 * Read and store the RANGE bit for later use
			 * This must be done before regulator is probed,
			 * otherwise we error in probe with unsupportable
			 * ranges. Read the current smps mode for later use.
			 */
			addr = rinfo->vsel_addr;
			desc->n_linear_ranges = 3;

			ret = palmas_smps_read(pmic->palmas, addr, &reg);
			if (ret)
				return ret;
			if (reg & PALMAS_SMPS12_VOLTAGE_RANGE)
				pmic->range[id] = 1;
			if (pmic->range[id])
				desc->linear_ranges = smps_high_ranges;
			else
				desc->linear_ranges = smps_low_ranges;

			if (reg_init && reg_init->roof_floor)
				desc->ops = &palmas_ops_ext_control_smps;
			else
				desc->ops = &palmas_ops_smps;
			desc->n_voltages = PALMAS_SMPS_NUM_VOLTAGES;
			desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    rinfo->vsel_addr);
			desc->vsel_mask = PALMAS_SMPS12_VOLTAGE_VSEL_MASK;

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
		}

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