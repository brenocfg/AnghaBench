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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gpio_irq_chip {int num_parents; int* parents; struct sprd_gpio* parent_handler_data; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  handler; int /*<<< orphan*/ * chip; } ;
struct TYPE_7__ {int base; struct gpio_irq_chip irq; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  of_node; TYPE_1__* parent; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  label; } ;
struct sprd_gpio {int irq; TYPE_3__ chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRD_GPIO_NR ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int devm_gpiochip_add_data (TYPE_1__*,TYPE_3__*,struct sprd_gpio*) ; 
 struct sprd_gpio* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_gpio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_gpio_direction_input ; 
 int /*<<< orphan*/  sprd_gpio_direction_output ; 
 int /*<<< orphan*/  sprd_gpio_free ; 
 int /*<<< orphan*/  sprd_gpio_get ; 
 int /*<<< orphan*/  sprd_gpio_irq_handler ; 
 int /*<<< orphan*/  sprd_gpio_irqchip ; 
 int /*<<< orphan*/  sprd_gpio_request ; 
 int /*<<< orphan*/  sprd_gpio_set ; 

__attribute__((used)) static int sprd_gpio_probe(struct platform_device *pdev)
{
	struct gpio_irq_chip *irq;
	struct sprd_gpio *sprd_gpio;
	int ret;

	sprd_gpio = devm_kzalloc(&pdev->dev, sizeof(*sprd_gpio), GFP_KERNEL);
	if (!sprd_gpio)
		return -ENOMEM;

	sprd_gpio->irq = platform_get_irq(pdev, 0);
	if (sprd_gpio->irq < 0)
		return sprd_gpio->irq;

	sprd_gpio->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(sprd_gpio->base))
		return PTR_ERR(sprd_gpio->base);

	spin_lock_init(&sprd_gpio->lock);

	sprd_gpio->chip.label = dev_name(&pdev->dev);
	sprd_gpio->chip.ngpio = SPRD_GPIO_NR;
	sprd_gpio->chip.base = -1;
	sprd_gpio->chip.parent = &pdev->dev;
	sprd_gpio->chip.of_node = pdev->dev.of_node;
	sprd_gpio->chip.request = sprd_gpio_request;
	sprd_gpio->chip.free = sprd_gpio_free;
	sprd_gpio->chip.get = sprd_gpio_get;
	sprd_gpio->chip.set = sprd_gpio_set;
	sprd_gpio->chip.direction_input = sprd_gpio_direction_input;
	sprd_gpio->chip.direction_output = sprd_gpio_direction_output;

	irq = &sprd_gpio->chip.irq;
	irq->chip = &sprd_gpio_irqchip;
	irq->handler = handle_bad_irq;
	irq->default_type = IRQ_TYPE_NONE;
	irq->parent_handler = sprd_gpio_irq_handler;
	irq->parent_handler_data = sprd_gpio;
	irq->num_parents = 1;
	irq->parents = &sprd_gpio->irq;

	ret = devm_gpiochip_add_data(&pdev->dev, &sprd_gpio->chip, sprd_gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, sprd_gpio);
	return 0;
}