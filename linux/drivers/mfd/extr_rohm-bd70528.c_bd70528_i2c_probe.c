#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct regmap_irq_type {int types_supported; int type_reg_offset; int type_rising_val; int type_falling_val; int type_level_high_val; int type_level_low_val; } ;
struct regmap_irq_chip_data {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_10__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  chip_type; } ;
struct bd70528_data {TYPE_3__ chip; int /*<<< orphan*/  rtc_timer_lock; } ;
struct TYPE_9__ {struct regmap_irq_type type; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_irqs; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int BD70528_INT_GPIO0 ; 
 int /*<<< orphan*/  BD70528_INT_GPIO_MASK ; 
 int BD70528_NUM_OF_GPIOS ; 
 int /*<<< orphan*/  BD70528_REG_INT_MAIN_MASK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int IRQ_TYPE_EDGE_BOTH ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int IRQ_TYPE_LEVEL_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROHM_CHIP_TYPE_BD70528 ; 
 TYPE_1__ bd70528_irq_chip ; 
 TYPE_2__* bd70528_irqs ; 
 TYPE_2__* bd70528_mfd_cells ; 
 int /*<<< orphan*/  bd70528_regmap ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,TYPE_3__*) ; 
 struct bd70528_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct regmap_irq_chip_data**) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (struct regmap_irq_chip_data*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bd70528_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct bd70528_data *bd70528;
	struct regmap_irq_chip_data *irq_data;
	int ret, i;

	if (!i2c->irq) {
		dev_err(&i2c->dev, "No IRQ configured\n");
		return -EINVAL;
	}

	bd70528 = devm_kzalloc(&i2c->dev, sizeof(*bd70528), GFP_KERNEL);
	if (!bd70528)
		return -ENOMEM;

	mutex_init(&bd70528->rtc_timer_lock);

	dev_set_drvdata(&i2c->dev, &bd70528->chip);

	bd70528->chip.chip_type = ROHM_CHIP_TYPE_BD70528;
	bd70528->chip.regmap = devm_regmap_init_i2c(i2c, &bd70528_regmap);
	if (IS_ERR(bd70528->chip.regmap)) {
		dev_err(&i2c->dev, "Failed to initialize Regmap\n");
		return PTR_ERR(bd70528->chip.regmap);
	}

	/*
	 * Disallow type setting for all IRQs by default as most of them do not
	 * support setting type.
	 */
	for (i = 0; i < ARRAY_SIZE(bd70528_irqs); i++)
		bd70528_irqs[i].type.types_supported = 0;

	/* Set IRQ typesetting information for GPIO pins 0 - 3 */
	for (i = 0; i < BD70528_NUM_OF_GPIOS; i++) {
		struct regmap_irq_type *type;

		type = &bd70528_irqs[BD70528_INT_GPIO0 + i].type;
		type->type_reg_offset = 2 * i;
		type->type_rising_val = 0x20;
		type->type_falling_val = 0x10;
		type->type_level_high_val = 0x40;
		type->type_level_low_val = 0x50;
		type->types_supported = (IRQ_TYPE_EDGE_BOTH |
				IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW);
	}

	ret = devm_regmap_add_irq_chip(&i2c->dev, bd70528->chip.regmap,
				       i2c->irq, IRQF_ONESHOT, 0,
				       &bd70528_irq_chip, &irq_data);
	if (ret) {
		dev_err(&i2c->dev, "Failed to add IRQ chip\n");
		return ret;
	}
	dev_dbg(&i2c->dev, "Registered %d IRQs for chip\n",
		bd70528_irq_chip.num_irqs);

	/*
	 * BD70528 IRQ controller is not touching the main mask register.
	 * So enable the GPIO block interrupts at main level. We can just leave
	 * them enabled as the IRQ controller should disable IRQs from
	 * sub-registers when IRQ is disabled or freed.
	 */
	ret = regmap_update_bits(bd70528->chip.regmap,
				 BD70528_REG_INT_MAIN_MASK,
				 BD70528_INT_GPIO_MASK, 0);

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO,
				   bd70528_mfd_cells,
				   ARRAY_SIZE(bd70528_mfd_cells), NULL, 0,
				   regmap_irq_get_domain(irq_data));
	if (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	return ret;
}