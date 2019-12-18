#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rk808_reg_data {int addr; int /*<<< orphan*/  value; int /*<<< orphan*/  mask; } ;
struct rk808 {int variant; int /*<<< orphan*/  irq_data; scalar_t__ pm_pwroff_prep_fn; scalar_t__ pm_pwroff_fn; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * regmap_irq_chip; int /*<<< orphan*/ * regmap_cfg; struct i2c_client* i2c; } ;
struct mfd_cell {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  RK805_ID 132 
#define  RK808_ID 131 
 int RK808_ID_LSB ; 
 int RK808_ID_MSB ; 
#define  RK809_ID 130 
#define  RK817_ID 129 
 unsigned char RK817_ID_LSB ; 
 unsigned char RK817_ID_MSB ; 
#define  RK818_ID 128 
 int RK8XX_ID_MSK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,unsigned int) ; 
 struct rk808* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (TYPE_1__*,int /*<<< orphan*/ ,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rk808*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,unsigned char) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ pm_power_off ; 
 scalar_t__ pm_power_off_prepare ; 
 int /*<<< orphan*/  register_syscore_ops (int /*<<< orphan*/ *) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rk805_device_shutdown ; 
 scalar_t__ rk805_device_shutdown_prepare ; 
 int /*<<< orphan*/  rk805_irq_chip ; 
 void* rk805_pre_init_reg ; 
 int /*<<< orphan*/  rk805_regmap_config ; 
 void* rk805s ; 
 scalar_t__ rk808_device_shutdown ; 
 struct i2c_client* rk808_i2c_client ; 
 int /*<<< orphan*/  rk808_irq_chip ; 
 void* rk808_pre_init_reg ; 
 int /*<<< orphan*/  rk808_regmap_config ; 
 int /*<<< orphan*/  rk808_syscore_ops ; 
 void* rk808s ; 
 int /*<<< orphan*/  rk817_irq_chip ; 
 void* rk817_pre_init_reg ; 
 int /*<<< orphan*/  rk817_regmap_config ; 
 void* rk817s ; 
 scalar_t__ rk818_device_shutdown ; 
 int /*<<< orphan*/  rk818_irq_chip ; 
 void* rk818_pre_init_reg ; 
 int /*<<< orphan*/  rk818_regmap_config ; 
 void* rk818s ; 

__attribute__((used)) static int rk808_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct device_node *np = client->dev.of_node;
	struct rk808 *rk808;
	const struct rk808_reg_data *pre_init_reg;
	const struct mfd_cell *cells;
	int nr_pre_init_regs;
	int nr_cells;
	int pm_off = 0, msb, lsb;
	unsigned char pmic_id_msb, pmic_id_lsb;
	int ret;
	int i;

	rk808 = devm_kzalloc(&client->dev, sizeof(*rk808), GFP_KERNEL);
	if (!rk808)
		return -ENOMEM;

	if (of_device_is_compatible(np, "rockchip,rk817") ||
	    of_device_is_compatible(np, "rockchip,rk809")) {
		pmic_id_msb = RK817_ID_MSB;
		pmic_id_lsb = RK817_ID_LSB;
	} else {
		pmic_id_msb = RK808_ID_MSB;
		pmic_id_lsb = RK808_ID_LSB;
	}

	/* Read chip variant */
	msb = i2c_smbus_read_byte_data(client, pmic_id_msb);
	if (msb < 0) {
		dev_err(&client->dev, "failed to read the chip id at 0x%x\n",
			RK808_ID_MSB);
		return msb;
	}

	lsb = i2c_smbus_read_byte_data(client, pmic_id_lsb);
	if (lsb < 0) {
		dev_err(&client->dev, "failed to read the chip id at 0x%x\n",
			RK808_ID_LSB);
		return lsb;
	}

	rk808->variant = ((msb << 8) | lsb) & RK8XX_ID_MSK;
	dev_info(&client->dev, "chip id: 0x%x\n", (unsigned int)rk808->variant);

	switch (rk808->variant) {
	case RK805_ID:
		rk808->regmap_cfg = &rk805_regmap_config;
		rk808->regmap_irq_chip = &rk805_irq_chip;
		pre_init_reg = rk805_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk805_pre_init_reg);
		cells = rk805s;
		nr_cells = ARRAY_SIZE(rk805s);
		rk808->pm_pwroff_fn = rk805_device_shutdown;
		rk808->pm_pwroff_prep_fn = rk805_device_shutdown_prepare;
		break;
	case RK808_ID:
		rk808->regmap_cfg = &rk808_regmap_config;
		rk808->regmap_irq_chip = &rk808_irq_chip;
		pre_init_reg = rk808_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk808_pre_init_reg);
		cells = rk808s;
		nr_cells = ARRAY_SIZE(rk808s);
		rk808->pm_pwroff_fn = rk808_device_shutdown;
		break;
	case RK818_ID:
		rk808->regmap_cfg = &rk818_regmap_config;
		rk808->regmap_irq_chip = &rk818_irq_chip;
		pre_init_reg = rk818_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk818_pre_init_reg);
		cells = rk818s;
		nr_cells = ARRAY_SIZE(rk818s);
		rk808->pm_pwroff_fn = rk818_device_shutdown;
		break;
	case RK809_ID:
	case RK817_ID:
		rk808->regmap_cfg = &rk817_regmap_config;
		rk808->regmap_irq_chip = &rk817_irq_chip;
		pre_init_reg = rk817_pre_init_reg;
		nr_pre_init_regs = ARRAY_SIZE(rk817_pre_init_reg);
		cells = rk817s;
		nr_cells = ARRAY_SIZE(rk817s);
		register_syscore_ops(&rk808_syscore_ops);
		break;
	default:
		dev_err(&client->dev, "Unsupported RK8XX ID %lu\n",
			rk808->variant);
		return -EINVAL;
	}

	rk808->i2c = client;
	i2c_set_clientdata(client, rk808);

	rk808->regmap = devm_regmap_init_i2c(client, rk808->regmap_cfg);
	if (IS_ERR(rk808->regmap)) {
		dev_err(&client->dev, "regmap initialization failed\n");
		return PTR_ERR(rk808->regmap);
	}

	if (!client->irq) {
		dev_err(&client->dev, "No interrupt support, no core IRQ\n");
		return -EINVAL;
	}

	ret = regmap_add_irq_chip(rk808->regmap, client->irq,
				  IRQF_ONESHOT, -1,
				  rk808->regmap_irq_chip, &rk808->irq_data);
	if (ret) {
		dev_err(&client->dev, "Failed to add irq_chip %d\n", ret);
		return ret;
	}

	for (i = 0; i < nr_pre_init_regs; i++) {
		ret = regmap_update_bits(rk808->regmap,
					pre_init_reg[i].addr,
					pre_init_reg[i].mask,
					pre_init_reg[i].value);
		if (ret) {
			dev_err(&client->dev,
				"0x%x write err\n",
				pre_init_reg[i].addr);
			return ret;
		}
	}

	ret = devm_mfd_add_devices(&client->dev, PLATFORM_DEVID_NONE,
			      cells, nr_cells, NULL, 0,
			      regmap_irq_get_domain(rk808->irq_data));
	if (ret) {
		dev_err(&client->dev, "failed to add MFD devices %d\n", ret);
		goto err_irq;
	}

	pm_off = of_property_read_bool(np,
				"rockchip,system-power-controller");
	if (pm_off && !pm_power_off) {
		rk808_i2c_client = client;
		pm_power_off = rk808->pm_pwroff_fn;
	}

	if (pm_off && !pm_power_off_prepare) {
		if (!rk808_i2c_client)
			rk808_i2c_client = client;
		pm_power_off_prepare = rk808->pm_pwroff_prep_fn;
	}

	return 0;

err_irq:
	regmap_del_irq_chip(client->irq, rk808->irq_data);
	return ret;
}