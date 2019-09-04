#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {int ngpio; TYPE_5__* parent; int /*<<< orphan*/  owner; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; } ;
struct TYPE_8__ {TYPE_3__ gc; } ;
struct altera_gpio_chip {scalar_t__ mapped_irq; int interrupt_trigger; TYPE_1__ mmchip; int /*<<< orphan*/  gpio_lock; } ;

/* Variables and functions */
 void* ALTERA_GPIO_MAX_NGPIO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  altera_gpio_direction_input ; 
 int /*<<< orphan*/  altera_gpio_direction_output ; 
 int /*<<< orphan*/  altera_gpio_get ; 
 int /*<<< orphan*/  altera_gpio_irq_edge_handler ; 
 int /*<<< orphan*/  altera_gpio_irq_leveL_high_handler ; 
 int /*<<< orphan*/  altera_gpio_set ; 
 int /*<<< orphan*/  altera_irq_chip ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_5__*,char*,void*,void*) ; 
 struct altera_gpio_chip* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_irqchip_add (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int of_mm_gpiochip_add_data (struct device_node*,TYPE_1__*,struct altera_gpio_chip*) ; 
 int /*<<< orphan*/  of_mm_gpiochip_remove (TYPE_1__*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct altera_gpio_chip*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int altera_gpio_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	int reg, ret;
	struct altera_gpio_chip *altera_gc;

	altera_gc = devm_kzalloc(&pdev->dev, sizeof(*altera_gc), GFP_KERNEL);
	if (!altera_gc)
		return -ENOMEM;

	raw_spin_lock_init(&altera_gc->gpio_lock);

	if (of_property_read_u32(node, "altr,ngpio", &reg))
		/* By default assume maximum ngpio */
		altera_gc->mmchip.gc.ngpio = ALTERA_GPIO_MAX_NGPIO;
	else
		altera_gc->mmchip.gc.ngpio = reg;

	if (altera_gc->mmchip.gc.ngpio > ALTERA_GPIO_MAX_NGPIO) {
		dev_warn(&pdev->dev,
			"ngpio is greater than %d, defaulting to %d\n",
			ALTERA_GPIO_MAX_NGPIO, ALTERA_GPIO_MAX_NGPIO);
		altera_gc->mmchip.gc.ngpio = ALTERA_GPIO_MAX_NGPIO;
	}

	altera_gc->mmchip.gc.direction_input	= altera_gpio_direction_input;
	altera_gc->mmchip.gc.direction_output	= altera_gpio_direction_output;
	altera_gc->mmchip.gc.get		= altera_gpio_get;
	altera_gc->mmchip.gc.set		= altera_gpio_set;
	altera_gc->mmchip.gc.owner		= THIS_MODULE;
	altera_gc->mmchip.gc.parent		= &pdev->dev;

	ret = of_mm_gpiochip_add_data(node, &altera_gc->mmchip, altera_gc);
	if (ret) {
		dev_err(&pdev->dev, "Failed adding memory mapped gpiochip\n");
		return ret;
	}

	platform_set_drvdata(pdev, altera_gc);

	altera_gc->mapped_irq = platform_get_irq(pdev, 0);

	if (altera_gc->mapped_irq < 0)
		goto skip_irq;

	if (of_property_read_u32(node, "altr,interrupt-type", &reg)) {
		ret = -EINVAL;
		dev_err(&pdev->dev,
			"altr,interrupt-type value not set in device tree\n");
		goto teardown;
	}
	altera_gc->interrupt_trigger = reg;

	ret = gpiochip_irqchip_add(&altera_gc->mmchip.gc, &altera_irq_chip, 0,
		handle_bad_irq, IRQ_TYPE_NONE);

	if (ret) {
		dev_err(&pdev->dev, "could not add irqchip\n");
		goto teardown;
	}

	gpiochip_set_chained_irqchip(&altera_gc->mmchip.gc,
		&altera_irq_chip,
		altera_gc->mapped_irq,
		altera_gc->interrupt_trigger == IRQ_TYPE_LEVEL_HIGH ?
		altera_gpio_irq_leveL_high_handler :
		altera_gpio_irq_edge_handler);

skip_irq:
	return 0;
teardown:
	of_mm_gpiochip_remove(&altera_gc->mmchip);
	pr_err("%pOF: registration failed with status %d\n",
		node, ret);

	return ret;
}