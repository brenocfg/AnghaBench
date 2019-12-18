#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timbgpio_platform_data {int nr_pins; scalar_t__ irq_base; int /*<<< orphan*/  gpio_base; } ;
struct gpio_chip {int ngpio; int can_sleep; int /*<<< orphan*/  base; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/ * to_irq; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; struct device* parent; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct timbgpio {scalar_t__ irq_base; scalar_t__ membase; struct gpio_chip gpio; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ TGPIO_IER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct timbgpio_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,struct timbgpio*) ; 
 struct timbgpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  irq_clear_status_flags (scalar_t__,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct timbgpio*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (scalar_t__,struct timbgpio*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct timbgpio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timbgpio_gpio_direction_input ; 
 int /*<<< orphan*/  timbgpio_gpio_direction_output ; 
 int /*<<< orphan*/  timbgpio_gpio_get ; 
 int /*<<< orphan*/  timbgpio_gpio_set ; 
 int /*<<< orphan*/  timbgpio_irq ; 
 int /*<<< orphan*/  timbgpio_irqchip ; 
 int /*<<< orphan*/ * timbgpio_to_irq ; 

__attribute__((used)) static int timbgpio_probe(struct platform_device *pdev)
{
	int err, i;
	struct device *dev = &pdev->dev;
	struct gpio_chip *gc;
	struct timbgpio *tgpio;
	struct timbgpio_platform_data *pdata = dev_get_platdata(&pdev->dev);
	int irq = platform_get_irq(pdev, 0);

	if (!pdata || pdata->nr_pins > 32) {
		dev_err(dev, "Invalid platform data\n");
		return -EINVAL;
	}

	tgpio = devm_kzalloc(dev, sizeof(*tgpio), GFP_KERNEL);
	if (!tgpio)
		return -EINVAL;

	tgpio->irq_base = pdata->irq_base;

	spin_lock_init(&tgpio->lock);

	tgpio->membase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(tgpio->membase))
		return PTR_ERR(tgpio->membase);

	gc = &tgpio->gpio;

	gc->label = dev_name(&pdev->dev);
	gc->owner = THIS_MODULE;
	gc->parent = &pdev->dev;
	gc->direction_input = timbgpio_gpio_direction_input;
	gc->get = timbgpio_gpio_get;
	gc->direction_output = timbgpio_gpio_direction_output;
	gc->set = timbgpio_gpio_set;
	gc->to_irq = (irq >= 0 && tgpio->irq_base > 0) ? timbgpio_to_irq : NULL;
	gc->dbg_show = NULL;
	gc->base = pdata->gpio_base;
	gc->ngpio = pdata->nr_pins;
	gc->can_sleep = false;

	err = devm_gpiochip_add_data(&pdev->dev, gc, tgpio);
	if (err)
		return err;

	platform_set_drvdata(pdev, tgpio);

	/* make sure to disable interrupts */
	iowrite32(0x0, tgpio->membase + TGPIO_IER);

	if (irq < 0 || tgpio->irq_base <= 0)
		return 0;

	for (i = 0; i < pdata->nr_pins; i++) {
		irq_set_chip_and_handler(tgpio->irq_base + i,
			&timbgpio_irqchip, handle_simple_irq);
		irq_set_chip_data(tgpio->irq_base + i, tgpio);
		irq_clear_status_flags(tgpio->irq_base + i, IRQ_NOREQUEST | IRQ_NOPROBE);
	}

	irq_set_chained_handler_and_data(irq, timbgpio_irq, tgpio);

	return 0;
}