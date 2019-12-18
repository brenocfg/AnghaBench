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
struct resource {scalar_t__ start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gpio_irq_chip {int num_parents; unsigned int* parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/  init_hw; int /*<<< orphan*/ * chip; } ;
struct gpio_chip {int base; int can_sleep; struct gpio_irq_chip irq; struct device* parent; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct lp_gpio {struct gpio_chip chip; int /*<<< orphan*/  lock; scalar_t__ reg_base; struct platform_device* pdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  LP_NUM_GPIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,struct lp_gpio*) ; 
 unsigned int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct lp_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,unsigned long,char*) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  lp_gpio_direction_input ; 
 int /*<<< orphan*/  lp_gpio_direction_output ; 
 int /*<<< orphan*/  lp_gpio_free ; 
 int /*<<< orphan*/  lp_gpio_get ; 
 int /*<<< orphan*/  lp_gpio_irq_handler ; 
 int /*<<< orphan*/  lp_gpio_irq_init_hw ; 
 int /*<<< orphan*/  lp_gpio_request ; 
 int /*<<< orphan*/  lp_gpio_set ; 
 int /*<<< orphan*/  lp_irqchip ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp_gpio*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 unsigned long resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp_gpio_probe(struct platform_device *pdev)
{
	struct lp_gpio *lg;
	struct gpio_chip *gc;
	struct resource *io_rc, *irq_rc;
	struct device *dev = &pdev->dev;
	unsigned long reg_len;
	int ret = -ENODEV;

	lg = devm_kzalloc(dev, sizeof(struct lp_gpio), GFP_KERNEL);
	if (!lg)
		return -ENOMEM;

	lg->pdev = pdev;
	platform_set_drvdata(pdev, lg);

	io_rc = platform_get_resource(pdev, IORESOURCE_IO, 0);
	irq_rc = platform_get_resource(pdev, IORESOURCE_IRQ, 0);

	if (!io_rc) {
		dev_err(dev, "missing IO resources\n");
		return -EINVAL;
	}

	lg->reg_base = io_rc->start;
	reg_len = resource_size(io_rc);

	if (!devm_request_region(dev, lg->reg_base, reg_len, "lp-gpio")) {
		dev_err(dev, "failed requesting IO region 0x%x\n",
			(unsigned int)lg->reg_base);
		return -EBUSY;
	}

	spin_lock_init(&lg->lock);

	gc = &lg->chip;
	gc->label = dev_name(dev);
	gc->owner = THIS_MODULE;
	gc->request = lp_gpio_request;
	gc->free = lp_gpio_free;
	gc->direction_input = lp_gpio_direction_input;
	gc->direction_output = lp_gpio_direction_output;
	gc->get = lp_gpio_get;
	gc->set = lp_gpio_set;
	gc->base = -1;
	gc->ngpio = LP_NUM_GPIO;
	gc->can_sleep = false;
	gc->parent = dev;

	/* set up interrupts  */
	if (irq_rc && irq_rc->start) {
		struct gpio_irq_chip *girq;

		girq = &gc->irq;
		girq->chip = &lp_irqchip;
		girq->init_hw = lp_gpio_irq_init_hw;
		girq->parent_handler = lp_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kcalloc(&pdev->dev, girq->num_parents,
					     sizeof(*girq->parents),
					     GFP_KERNEL);
		if (!girq->parents)
			return -ENOMEM;
		girq->parents[0] = (unsigned)irq_rc->start;
		girq->default_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
	}

	ret = devm_gpiochip_add_data(dev, gc, lg);
	if (ret) {
		dev_err(dev, "failed adding lp-gpio chip\n");
		return ret;
	}

	pm_runtime_enable(dev);

	return 0;
}