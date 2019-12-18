#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct palmas_platform_data {int irq_flags; unsigned int pad1; unsigned int pad2; unsigned int power_ctrl; scalar_t__ pm_off; scalar_t__ mux_from_pdata; } ;
struct palmas_driver_data {int /*<<< orphan*/  irq_chip; int /*<<< orphan*/ * features; } ;
struct palmas {struct i2c_client** i2c_clients; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; struct i2c_client** regmap; int /*<<< orphan*/  led_muxed; int /*<<< orphan*/  pwm_muxed; int /*<<< orphan*/  gpio_muxed; TYPE_1__* dev; int /*<<< orphan*/  features; } ;
struct of_device_id {scalar_t__ data; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; scalar_t__ addr; int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 unsigned int PALMAS_BASE_TO_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PALMAS_BASE_TO_SLAVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PALMAS_GPIO_0_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_1_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_2_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_3_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_4_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_5_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_6_MUXED ; 
 int /*<<< orphan*/  PALMAS_GPIO_7_MUXED ; 
 int /*<<< orphan*/  PALMAS_INTERRUPT_BASE ; 
 int /*<<< orphan*/  PALMAS_INT_CTRL ; 
 unsigned int PALMAS_INT_CTRL_INT_CLEAR ; 
 int /*<<< orphan*/  PALMAS_LED1_MUXED ; 
 int /*<<< orphan*/  PALMAS_LED2_MUXED ; 
 int PALMAS_NUM_CLIENTS ; 
 int /*<<< orphan*/  PALMAS_PMU_CONTROL_BASE ; 
 int /*<<< orphan*/  PALMAS_POLARITY_CTRL ; 
 unsigned int PALMAS_POLARITY_CTRL_INT_POLARITY ; 
 int /*<<< orphan*/  PALMAS_POWER_CTRL ; 
 int /*<<< orphan*/  PALMAS_PRIMARY_SECONDARY_PAD1 ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_0 ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK ; 
 int PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK ; 
 int PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_SHIFT ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_3 ; 
 int /*<<< orphan*/  PALMAS_PRIMARY_SECONDARY_PAD2 ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_4 ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_5_MASK ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_6 ; 
 unsigned int PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_7_MASK ; 
 int /*<<< orphan*/  PALMAS_PU_PD_OD_BASE ; 
 int /*<<< orphan*/  PALMAS_PWM1_MUXED ; 
 int /*<<< orphan*/  PALMAS_PWM2_MUXED ; 
 int PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,...) ; 
 struct palmas_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (TYPE_1__*) ; 
 struct i2c_client* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct i2c_client* i2c_new_dummy_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct palmas*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_palmas_match_tbl ; 
 struct palmas* palmas_dev ; 
 int /*<<< orphan*/  palmas_dt_to_pdata (struct i2c_client*,struct palmas_platform_data*) ; 
 scalar_t__ palmas_power_off ; 
 int /*<<< orphan*/ * palmas_regmap_config ; 
 int palmas_update_bits (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ pm_power_off ; 
 int regmap_add_irq_chip (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (struct i2c_client*,unsigned int,unsigned int*) ; 
 int regmap_write (struct i2c_client*,unsigned int,unsigned int) ; 

__attribute__((used)) static int palmas_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct palmas *palmas;
	struct palmas_platform_data *pdata;
	struct palmas_driver_data *driver_data;
	struct device_node *node = i2c->dev.of_node;
	int ret = 0, i;
	unsigned int reg, addr;
	int slave;
	const struct of_device_id *match;

	pdata = dev_get_platdata(&i2c->dev);

	if (node && !pdata) {
		pdata = devm_kzalloc(&i2c->dev, sizeof(*pdata), GFP_KERNEL);

		if (!pdata)
			return -ENOMEM;

		palmas_dt_to_pdata(i2c, pdata);
	}

	if (!pdata)
		return -EINVAL;

	palmas = devm_kzalloc(&i2c->dev, sizeof(struct palmas), GFP_KERNEL);
	if (palmas == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, palmas);
	palmas->dev = &i2c->dev;
	palmas->irq = i2c->irq;

	match = of_match_device(of_palmas_match_tbl, &i2c->dev);

	if (!match)
		return -ENODATA;

	driver_data = (struct palmas_driver_data *)match->data;
	palmas->features = *driver_data->features;

	for (i = 0; i < PALMAS_NUM_CLIENTS; i++) {
		if (i == 0)
			palmas->i2c_clients[i] = i2c;
		else {
			palmas->i2c_clients[i] =
					i2c_new_dummy_device(i2c->adapter,
							i2c->addr + i);
			if (IS_ERR(palmas->i2c_clients[i])) {
				dev_err(palmas->dev,
					"can't attach client %d\n", i);
				ret = PTR_ERR(palmas->i2c_clients[i]);
				goto err_i2c;
			}
			palmas->i2c_clients[i]->dev.of_node = of_node_get(node);
		}
		palmas->regmap[i] = devm_regmap_init_i2c(palmas->i2c_clients[i],
				&palmas_regmap_config[i]);
		if (IS_ERR(palmas->regmap[i])) {
			ret = PTR_ERR(palmas->regmap[i]);
			dev_err(palmas->dev,
				"Failed to allocate regmap %d, err: %d\n",
				i, ret);
			goto err_i2c;
		}
	}

	if (!palmas->irq) {
		dev_warn(palmas->dev, "IRQ missing: skipping irq request\n");
		goto no_irq;
	}

	/* Change interrupt line output polarity */
	if (pdata->irq_flags & IRQ_TYPE_LEVEL_HIGH)
		reg = PALMAS_POLARITY_CTRL_INT_POLARITY;
	else
		reg = 0;
	ret = palmas_update_bits(palmas, PALMAS_PU_PD_OD_BASE,
			PALMAS_POLARITY_CTRL, PALMAS_POLARITY_CTRL_INT_POLARITY,
			reg);
	if (ret < 0) {
		dev_err(palmas->dev, "POLARITY_CTRL update failed: %d\n", ret);
		goto err_i2c;
	}

	/* Change IRQ into clear on read mode for efficiency */
	slave = PALMAS_BASE_TO_SLAVE(PALMAS_INTERRUPT_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_INTERRUPT_BASE, PALMAS_INT_CTRL);
	reg = PALMAS_INT_CTRL_INT_CLEAR;

	regmap_write(palmas->regmap[slave], addr, reg);

	ret = regmap_add_irq_chip(palmas->regmap[slave], palmas->irq,
				  IRQF_ONESHOT | pdata->irq_flags, 0,
				  driver_data->irq_chip, &palmas->irq_data);
	if (ret < 0)
		goto err_i2c;

no_irq:
	slave = PALMAS_BASE_TO_SLAVE(PALMAS_PU_PD_OD_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD1);

	if (pdata->mux_from_pdata) {
		reg = pdata->pad1;
		ret = regmap_write(palmas->regmap[slave], addr, reg);
		if (ret)
			goto err_irq;
	} else {
		ret = regmap_read(palmas->regmap[slave], addr, &reg);
		if (ret)
			goto err_irq;
	}

	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_0))
		palmas->gpio_muxed |= PALMAS_GPIO_0_MUXED;
	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_1_MUXED;
	else if ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK) ==
			(2 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT))
		palmas->led_muxed |= PALMAS_LED1_MUXED;
	else if ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK) ==
			(3 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT))
		palmas->pwm_muxed |= PALMAS_PWM1_MUXED;
	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_2_MUXED;
	else if ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK) ==
			(2 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_SHIFT))
		palmas->led_muxed |= PALMAS_LED2_MUXED;
	else if ((reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_MASK) ==
			(3 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_2_SHIFT))
		palmas->pwm_muxed |= PALMAS_PWM2_MUXED;
	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_3))
		palmas->gpio_muxed |= PALMAS_GPIO_3_MUXED;

	addr = PALMAS_BASE_TO_REG(PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD2);

	if (pdata->mux_from_pdata) {
		reg = pdata->pad2;
		ret = regmap_write(palmas->regmap[slave], addr, reg);
		if (ret)
			goto err_irq;
	} else {
		ret = regmap_read(palmas->regmap[slave], addr, &reg);
		if (ret)
			goto err_irq;
	}

	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_4))
		palmas->gpio_muxed |= PALMAS_GPIO_4_MUXED;
	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_5_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_5_MUXED;
	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_6))
		palmas->gpio_muxed |= PALMAS_GPIO_6_MUXED;
	if (!(reg & PALMAS_PRIMARY_SECONDARY_PAD2_GPIO_7_MASK))
		palmas->gpio_muxed |= PALMAS_GPIO_7_MUXED;

	dev_info(palmas->dev, "Muxing GPIO %x, PWM %x, LED %x\n",
			palmas->gpio_muxed, palmas->pwm_muxed,
			palmas->led_muxed);

	reg = pdata->power_ctrl;

	slave = PALMAS_BASE_TO_SLAVE(PALMAS_PMU_CONTROL_BASE);
	addr = PALMAS_BASE_TO_REG(PALMAS_PMU_CONTROL_BASE, PALMAS_POWER_CTRL);

	ret = regmap_write(palmas->regmap[slave], addr, reg);
	if (ret)
		goto err_irq;

	/*
	 * If we are probing with DT do this the DT way and return here
	 * otherwise continue and add devices using mfd helpers.
	 */
	if (node) {
		ret = devm_of_platform_populate(&i2c->dev);
		if (ret < 0) {
			goto err_irq;
		} else if (pdata->pm_off && !pm_power_off) {
			palmas_dev = palmas;
			pm_power_off = palmas_power_off;
		}
	}

	return ret;

err_irq:
	regmap_del_irq_chip(palmas->irq, palmas->irq_data);
err_i2c:
	for (i = 1; i < PALMAS_NUM_CLIENTS; i++) {
		if (palmas->i2c_clients[i])
			i2c_unregister_device(palmas->i2c_clients[i]);
	}
	return ret;
}