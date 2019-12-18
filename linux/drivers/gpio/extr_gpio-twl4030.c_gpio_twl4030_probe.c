#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct twl4030_gpio_platform_data {int (* setup ) (TYPE_1__*,int,scalar_t__) ;scalar_t__ use_leds; int /*<<< orphan*/  mmc_cd; int /*<<< orphan*/  debounce; int /*<<< orphan*/  pulldowns; int /*<<< orphan*/  pullups; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_12__ {int base; scalar_t__ ngpio; TYPE_1__* parent; } ;
struct gpio_twl4030_priv {int irq_base; TYPE_2__ gpio_chip; int /*<<< orphan*/  mutex; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TWL4030_GPIO_MAX ; 
 int /*<<< orphan*/  TWL4030_MODULE_GPIO ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct twl4030_gpio_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int devm_irq_alloc_descs (TYPE_1__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct gpio_twl4030_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int gpio_twl4030_debounce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_twl4030_pulls (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_twl4030_remove (struct platform_device*) ; 
 int gpiochip_add_data (TYPE_2__*,struct gpio_twl4030_priv*) ; 
 int /*<<< orphan*/  irq_domain_add_legacy (struct device_node*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_simple_ops ; 
 scalar_t__ is_module () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct twl4030_gpio_platform_data* of_gpio_twl4030 (TYPE_1__*,struct twl4030_gpio_platform_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_twl4030_priv*) ; 
 int stub1 (TYPE_1__*,int,scalar_t__) ; 
 TYPE_2__ template_chip ; 
 int twl4030_sih_setup (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpio_twl4030_probe(struct platform_device *pdev)
{
	struct twl4030_gpio_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct device_node *node = pdev->dev.of_node;
	struct gpio_twl4030_priv *priv;
	int ret, irq_base;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct gpio_twl4030_priv),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* maybe setup IRQs */
	if (is_module()) {
		dev_err(&pdev->dev, "can't dispatch IRQs from modules\n");
		goto no_irqs;
	}

	irq_base = devm_irq_alloc_descs(&pdev->dev, -1,
					0, TWL4030_GPIO_MAX, 0);
	if (irq_base < 0) {
		dev_err(&pdev->dev, "Failed to alloc irq_descs\n");
		return irq_base;
	}

	irq_domain_add_legacy(node, TWL4030_GPIO_MAX, irq_base, 0,
			      &irq_domain_simple_ops, NULL);

	ret = twl4030_sih_setup(&pdev->dev, TWL4030_MODULE_GPIO, irq_base);
	if (ret < 0)
		return ret;

	priv->irq_base = irq_base;

no_irqs:
	priv->gpio_chip = template_chip;
	priv->gpio_chip.base = -1;
	priv->gpio_chip.ngpio = TWL4030_GPIO_MAX;
	priv->gpio_chip.parent = &pdev->dev;

	mutex_init(&priv->mutex);

	if (node)
		pdata = of_gpio_twl4030(&pdev->dev, pdata);

	if (pdata == NULL) {
		dev_err(&pdev->dev, "Platform data is missing\n");
		return -ENXIO;
	}

	/*
	 * NOTE:  boards may waste power if they don't set pullups
	 * and pulldowns correctly ... default for non-ULPI pins is
	 * pulldown, and some other pins may have external pullups
	 * or pulldowns.  Careful!
	 */
	ret = gpio_twl4030_pulls(pdata->pullups, pdata->pulldowns);
	if (ret)
		dev_dbg(&pdev->dev, "pullups %.05x %.05x --> %d\n",
			pdata->pullups, pdata->pulldowns, ret);

	ret = gpio_twl4030_debounce(pdata->debounce, pdata->mmc_cd);
	if (ret)
		dev_dbg(&pdev->dev, "debounce %.03x %.01x --> %d\n",
			pdata->debounce, pdata->mmc_cd, ret);

	/*
	 * NOTE: we assume VIBRA_CTL.VIBRA_EN, in MODULE_AUDIO_VOICE,
	 * is (still) clear if use_leds is set.
	 */
	if (pdata->use_leds)
		priv->gpio_chip.ngpio += 2;

	ret = gpiochip_add_data(&priv->gpio_chip, priv);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not register gpiochip, %d\n", ret);
		priv->gpio_chip.ngpio = 0;
		gpio_twl4030_remove(pdev);
		goto out;
	}

	platform_set_drvdata(pdev, priv);

	if (pdata->setup) {
		int status;

		status = pdata->setup(&pdev->dev, priv->gpio_chip.base,
				      TWL4030_GPIO_MAX);
		if (status)
			dev_dbg(&pdev->dev, "setup --> %d\n", status);
	}

out:
	return ret;
}