#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ngpio; int can_sleep; int base; scalar_t__ of_node; TYPE_2__* parent; int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; } ;
struct tps65910_gpio {TYPE_5__ gpio_chip; struct tps65910* tps65910; } ;
struct tps65910_board {int gpio_base; int /*<<< orphan*/ * en_gpio_sleep; } ;
struct tps65910 {TYPE_6__* dev; TYPE_1__* i2c_client; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_12__ {scalar_t__ of_node; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_SLEEP_MASK ; 
 int /*<<< orphan*/  THIS_MODULE ; 
#define  TPS65910 129 
 scalar_t__ TPS65910_GPIO0 ; 
 int TPS65910_NUM_GPIO ; 
#define  TPS65911 128 
 int TPS65911_NUM_GPIO ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps65910_board* dev_get_platdata (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_6__*,char*,int) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_5__*,struct tps65910_gpio*) ; 
 struct tps65910_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65910_gpio*) ; 
 int tps65910_chip_id (struct tps65910*) ; 
 int /*<<< orphan*/  tps65910_gpio_get ; 
 int /*<<< orphan*/  tps65910_gpio_input ; 
 int /*<<< orphan*/  tps65910_gpio_output ; 
 int /*<<< orphan*/  tps65910_gpio_set ; 
 struct tps65910_board* tps65910_parse_dt_for_gpio (TYPE_2__*,struct tps65910*,int) ; 
 int tps65910_reg_set_bits (struct tps65910*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_gpio_probe(struct platform_device *pdev)
{
	struct tps65910 *tps65910 = dev_get_drvdata(pdev->dev.parent);
	struct tps65910_board *pdata = dev_get_platdata(tps65910->dev);
	struct tps65910_gpio *tps65910_gpio;
	int ret;
	int i;

	tps65910_gpio = devm_kzalloc(&pdev->dev,
				sizeof(*tps65910_gpio), GFP_KERNEL);
	if (!tps65910_gpio)
		return -ENOMEM;

	tps65910_gpio->tps65910 = tps65910;

	tps65910_gpio->gpio_chip.owner = THIS_MODULE;
	tps65910_gpio->gpio_chip.label = tps65910->i2c_client->name;

	switch (tps65910_chip_id(tps65910)) {
	case TPS65910:
		tps65910_gpio->gpio_chip.ngpio = TPS65910_NUM_GPIO;
		break;
	case TPS65911:
		tps65910_gpio->gpio_chip.ngpio = TPS65911_NUM_GPIO;
		break;
	default:
		return -EINVAL;
	}
	tps65910_gpio->gpio_chip.can_sleep = true;
	tps65910_gpio->gpio_chip.direction_input = tps65910_gpio_input;
	tps65910_gpio->gpio_chip.direction_output = tps65910_gpio_output;
	tps65910_gpio->gpio_chip.set	= tps65910_gpio_set;
	tps65910_gpio->gpio_chip.get	= tps65910_gpio_get;
	tps65910_gpio->gpio_chip.parent = &pdev->dev;
#ifdef CONFIG_OF_GPIO
	tps65910_gpio->gpio_chip.of_node = tps65910->dev->of_node;
#endif
	if (pdata && pdata->gpio_base)
		tps65910_gpio->gpio_chip.base = pdata->gpio_base;
	else
		tps65910_gpio->gpio_chip.base = -1;

	if (!pdata && tps65910->dev->of_node)
		pdata = tps65910_parse_dt_for_gpio(&pdev->dev, tps65910,
			tps65910_gpio->gpio_chip.ngpio);

	if (!pdata)
		goto skip_init;

	/* Configure sleep control for gpios if provided */
	for (i = 0; i < tps65910_gpio->gpio_chip.ngpio; ++i) {
		if (!pdata->en_gpio_sleep[i])
			continue;

		ret = tps65910_reg_set_bits(tps65910,
			TPS65910_GPIO0 + i, GPIO_SLEEP_MASK);
		if (ret < 0)
			dev_warn(tps65910->dev,
				"GPIO Sleep setting failed with err %d\n", ret);
	}

skip_init:
	ret = devm_gpiochip_add_data(&pdev->dev, &tps65910_gpio->gpio_chip,
				     tps65910_gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, tps65910_gpio);

	return ret;
}