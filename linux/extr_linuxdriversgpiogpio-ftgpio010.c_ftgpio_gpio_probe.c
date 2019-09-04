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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {char* label; int base; int /*<<< orphan*/  owner; struct device* parent; } ;
struct ftgpio_gpio {scalar_t__ base; TYPE_1__ gc; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO_DATA_CLR ; 
 scalar_t__ GPIO_DATA_IN ; 
 scalar_t__ GPIO_DATA_SET ; 
 scalar_t__ GPIO_DIR ; 
 scalar_t__ GPIO_INT_CLR ; 
 scalar_t__ GPIO_INT_EN ; 
 scalar_t__ GPIO_INT_MASK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int bgpio_init (TYPE_1__*,struct device*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct ftgpio_gpio*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ftgpio_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftgpio_gpio_irq_handler ; 
 int /*<<< orphan*/  ftgpio_gpio_irqchip ; 
 int gpiochip_irqchip_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ftgpio_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct ftgpio_gpio *g;
	int irq;
	int ret;

	g = devm_kzalloc(dev, sizeof(*g), GFP_KERNEL);
	if (!g)
		return -ENOMEM;

	g->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	g->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(g->base))
		return PTR_ERR(g->base);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq ? irq : -EINVAL;

	ret = bgpio_init(&g->gc, dev, 4,
			 g->base + GPIO_DATA_IN,
			 g->base + GPIO_DATA_SET,
			 g->base + GPIO_DATA_CLR,
			 g->base + GPIO_DIR,
			 NULL,
			 0);
	if (ret) {
		dev_err(dev, "unable to init generic GPIO\n");
		return ret;
	}
	g->gc.label = "FTGPIO010";
	g->gc.base = -1;
	g->gc.parent = dev;
	g->gc.owner = THIS_MODULE;
	/* ngpio is set by bgpio_init() */

	ret = devm_gpiochip_add_data(dev, &g->gc, g);
	if (ret)
		return ret;

	/* Disable, unmask and clear all interrupts */
	writel(0x0, g->base + GPIO_INT_EN);
	writel(0x0, g->base + GPIO_INT_MASK);
	writel(~0x0, g->base + GPIO_INT_CLR);

	ret = gpiochip_irqchip_add(&g->gc, &ftgpio_gpio_irqchip,
				   0, handle_bad_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_info(dev, "could not add irqchip\n");
		return ret;
	}
	gpiochip_set_chained_irqchip(&g->gc, &ftgpio_gpio_irqchip,
				     irq, ftgpio_gpio_irq_handler);

	dev_info(dev, "FTGPIO010 @%p registered\n", g->base);

	return 0;
}