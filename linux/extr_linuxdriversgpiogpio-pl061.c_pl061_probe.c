#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; void* name; } ;
struct TYPE_7__ {int base; int /*<<< orphan*/  owner; struct device* parent; void* label; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; } ;
struct pl061 {int parent_irq; TYPE_2__ irq_chip; TYPE_1__ gc; scalar_t__ base; int /*<<< orphan*/  lock; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct amba_id {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  start; } ;
struct amba_device {int* irq; TYPE_6__ res; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIOIE ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  PL061_GPIO_NR ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct pl061*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 void* dev_name (struct device*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,TYPE_6__*) ; 
 struct pl061* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct pl061*) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int gpiochip_irqchip_add (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pl061_direction_input ; 
 int /*<<< orphan*/  pl061_direction_output ; 
 int /*<<< orphan*/  pl061_get_direction ; 
 int /*<<< orphan*/  pl061_get_value ; 
 int /*<<< orphan*/  pl061_irq_ack ; 
 int /*<<< orphan*/  pl061_irq_handler ; 
 int /*<<< orphan*/  pl061_irq_mask ; 
 int /*<<< orphan*/  pl061_irq_set_wake ; 
 int /*<<< orphan*/  pl061_irq_type ; 
 int /*<<< orphan*/  pl061_irq_unmask ; 
 int /*<<< orphan*/  pl061_set_value ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pl061_probe(struct amba_device *adev, const struct amba_id *id)
{
	struct device *dev = &adev->dev;
	struct pl061 *pl061;
	int ret, irq;

	pl061 = devm_kzalloc(dev, sizeof(*pl061), GFP_KERNEL);
	if (pl061 == NULL)
		return -ENOMEM;

	pl061->base = devm_ioremap_resource(dev, &adev->res);
	if (IS_ERR(pl061->base))
		return PTR_ERR(pl061->base);

	raw_spin_lock_init(&pl061->lock);
	if (of_property_read_bool(dev->of_node, "gpio-ranges")) {
		pl061->gc.request = gpiochip_generic_request;
		pl061->gc.free = gpiochip_generic_free;
	}

	pl061->gc.base = -1;
	pl061->gc.get_direction = pl061_get_direction;
	pl061->gc.direction_input = pl061_direction_input;
	pl061->gc.direction_output = pl061_direction_output;
	pl061->gc.get = pl061_get_value;
	pl061->gc.set = pl061_set_value;
	pl061->gc.ngpio = PL061_GPIO_NR;
	pl061->gc.label = dev_name(dev);
	pl061->gc.parent = dev;
	pl061->gc.owner = THIS_MODULE;

	ret = gpiochip_add_data(&pl061->gc, pl061);
	if (ret)
		return ret;

	/*
	 * irq_chip support
	 */
	pl061->irq_chip.name = dev_name(dev);
	pl061->irq_chip.irq_ack	= pl061_irq_ack;
	pl061->irq_chip.irq_mask = pl061_irq_mask;
	pl061->irq_chip.irq_unmask = pl061_irq_unmask;
	pl061->irq_chip.irq_set_type = pl061_irq_type;
	pl061->irq_chip.irq_set_wake = pl061_irq_set_wake;

	writeb(0, pl061->base + GPIOIE); /* disable irqs */
	irq = adev->irq[0];
	if (irq < 0) {
		dev_err(&adev->dev, "invalid IRQ\n");
		return -ENODEV;
	}
	pl061->parent_irq = irq;

	ret = gpiochip_irqchip_add(&pl061->gc, &pl061->irq_chip,
				   0, handle_bad_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_info(&adev->dev, "could not add irqchip\n");
		return ret;
	}
	gpiochip_set_chained_irqchip(&pl061->gc, &pl061->irq_chip,
				     irq, pl061_irq_handler);

	amba_set_drvdata(adev, pl061);
	dev_info(&adev->dev, "PL061 GPIO chip @%pa registered\n",
		 &adev->res.start);

	return 0;
}