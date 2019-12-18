#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gpio_irq_chip {int num_parents; int* parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; TYPE_1__* chip; } ;
struct TYPE_5__ {char* label; int base; struct gpio_irq_chip irq; int /*<<< orphan*/  set_config; int /*<<< orphan*/  owner; struct device* parent; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; } ;
struct ftgpio_gpio {scalar_t__ clk; scalar_t__ base; TYPE_2__ gc; TYPE_1__ irq; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO_DATA_CLR ; 
 scalar_t__ GPIO_DATA_IN ; 
 scalar_t__ GPIO_DATA_SET ; 
 scalar_t__ GPIO_DEBOUNCE_EN ; 
 scalar_t__ GPIO_DIR ; 
 scalar_t__ GPIO_INT_CLR ; 
 scalar_t__ GPIO_INT_EN ; 
 scalar_t__ GPIO_INT_MASK ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int bgpio_init (TYPE_2__*,struct device*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__) ; 
 scalar_t__ devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_2__*,struct ftgpio_gpio*) ; 
 int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct ftgpio_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftgpio_gpio_ack_irq ; 
 int /*<<< orphan*/  ftgpio_gpio_irq_handler ; 
 int /*<<< orphan*/  ftgpio_gpio_mask_irq ; 
 int /*<<< orphan*/  ftgpio_gpio_set_config ; 
 int /*<<< orphan*/  ftgpio_gpio_set_irq_type ; 
 int /*<<< orphan*/  ftgpio_gpio_unmask_irq ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ftgpio_gpio*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ftgpio_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ftgpio_gpio *g;
	struct gpio_irq_chip *girq;
	int irq;
	int ret;

	g = devm_kzalloc(dev, sizeof(*g), GFP_KERNEL);
	if (!g)
		return -ENOMEM;

	g->dev = dev;

	g->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(g->base))
		return PTR_ERR(g->base);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq ? irq : -EINVAL;

	g->clk = devm_clk_get(dev, NULL);
	if (!IS_ERR(g->clk)) {
		ret = clk_prepare_enable(g->clk);
		if (ret)
			return ret;
	} else if (PTR_ERR(g->clk) == -EPROBE_DEFER) {
		/*
		 * Percolate deferrals, for anything else,
		 * just live without the clocking.
		 */
		return PTR_ERR(g->clk);
	}

	ret = bgpio_init(&g->gc, dev, 4,
			 g->base + GPIO_DATA_IN,
			 g->base + GPIO_DATA_SET,
			 g->base + GPIO_DATA_CLR,
			 g->base + GPIO_DIR,
			 NULL,
			 0);
	if (ret) {
		dev_err(dev, "unable to init generic GPIO\n");
		goto dis_clk;
	}
	g->gc.label = "FTGPIO010";
	g->gc.base = -1;
	g->gc.parent = dev;
	g->gc.owner = THIS_MODULE;
	/* ngpio is set by bgpio_init() */

	/* We need a silicon clock to do debounce */
	if (!IS_ERR(g->clk))
		g->gc.set_config = ftgpio_gpio_set_config;

	g->irq.name = "FTGPIO010";
	g->irq.irq_ack = ftgpio_gpio_ack_irq;
	g->irq.irq_mask = ftgpio_gpio_mask_irq;
	g->irq.irq_unmask = ftgpio_gpio_unmask_irq;
	g->irq.irq_set_type = ftgpio_gpio_set_irq_type;

	girq = &g->gc.irq;
	girq->chip = &g->irq;
	girq->parent_handler = ftgpio_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kcalloc(dev, 1, sizeof(*girq->parents),
				     GFP_KERNEL);
	if (!girq->parents) {
		ret = -ENOMEM;
		goto dis_clk;
	}
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = irq;

	/* Disable, unmask and clear all interrupts */
	writel(0x0, g->base + GPIO_INT_EN);
	writel(0x0, g->base + GPIO_INT_MASK);
	writel(~0x0, g->base + GPIO_INT_CLR);

	/* Clear any use of debounce */
	writel(0x0, g->base + GPIO_DEBOUNCE_EN);

	ret = devm_gpiochip_add_data(dev, &g->gc, g);
	if (ret)
		goto dis_clk;

	platform_set_drvdata(pdev, g);
	dev_info(dev, "FTGPIO010 @%p registered\n", g->base);

	return 0;

dis_clk:
	if (!IS_ERR(g->clk))
		clk_disable_unprepare(g->clk);
	return ret;
}