#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_13__ {int base; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; TYPE_5__* parent; int /*<<< orphan*/  label; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  ngpio; } ;
struct plgpio {int /*<<< orphan*/  clk; TYPE_1__ chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  csave_regs; int /*<<< orphan*/  base; } ;
struct TYPE_14__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_5__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_GPIO_PER_REG ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_5__*,struct resource*) ; 
 int /*<<< orphan*/  devm_kcalloc (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct plgpio* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct plgpio*) ; 
 int gpiochip_irqchip_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct plgpio*) ; 
 int /*<<< orphan*/  plgpio_direction_input ; 
 int /*<<< orphan*/  plgpio_direction_output ; 
 int /*<<< orphan*/  plgpio_free ; 
 int /*<<< orphan*/  plgpio_get_value ; 
 int /*<<< orphan*/  plgpio_irq_handler ; 
 int /*<<< orphan*/  plgpio_irqchip ; 
 int plgpio_probe_dt (struct platform_device*,struct plgpio*) ; 
 int /*<<< orphan*/  plgpio_request ; 
 int /*<<< orphan*/  plgpio_set_value ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int plgpio_probe(struct platform_device *pdev)
{
	struct plgpio *plgpio;
	struct resource *res;
	int ret, irq;

	plgpio = devm_kzalloc(&pdev->dev, sizeof(*plgpio), GFP_KERNEL);
	if (!plgpio)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	plgpio->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(plgpio->base))
		return PTR_ERR(plgpio->base);

	ret = plgpio_probe_dt(pdev, plgpio);
	if (ret) {
		dev_err(&pdev->dev, "DT probe failed\n");
		return ret;
	}

	plgpio->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(plgpio->clk))
		dev_warn(&pdev->dev, "clk_get() failed, work without it\n");

#ifdef CONFIG_PM_SLEEP
	plgpio->csave_regs = devm_kcalloc(&pdev->dev,
			DIV_ROUND_UP(plgpio->chip.ngpio, MAX_GPIO_PER_REG),
			sizeof(*plgpio->csave_regs),
			GFP_KERNEL);
	if (!plgpio->csave_regs)
		return -ENOMEM;
#endif

	platform_set_drvdata(pdev, plgpio);
	spin_lock_init(&plgpio->lock);

	plgpio->chip.base = -1;
	plgpio->chip.request = plgpio_request;
	plgpio->chip.free = plgpio_free;
	plgpio->chip.direction_input = plgpio_direction_input;
	plgpio->chip.direction_output = plgpio_direction_output;
	plgpio->chip.get = plgpio_get_value;
	plgpio->chip.set = plgpio_set_value;
	plgpio->chip.label = dev_name(&pdev->dev);
	plgpio->chip.parent = &pdev->dev;
	plgpio->chip.owner = THIS_MODULE;
	plgpio->chip.of_node = pdev->dev.of_node;

	if (!IS_ERR(plgpio->clk)) {
		ret = clk_prepare(plgpio->clk);
		if (ret) {
			dev_err(&pdev->dev, "clk prepare failed\n");
			return ret;
		}
	}

	ret = gpiochip_add_data(&plgpio->chip, plgpio);
	if (ret) {
		dev_err(&pdev->dev, "unable to add gpio chip\n");
		goto unprepare_clk;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_info(&pdev->dev, "PLGPIO registered without IRQs\n");
		return 0;
	}

	ret = gpiochip_irqchip_add(&plgpio->chip,
				   &plgpio_irqchip,
				   0,
				   handle_simple_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_err(&pdev->dev, "failed to add irqchip to gpiochip\n");
		goto remove_gpiochip;
	}

	gpiochip_set_chained_irqchip(&plgpio->chip,
				     &plgpio_irqchip,
				     irq,
				     plgpio_irq_handler);

	dev_info(&pdev->dev, "PLGPIO registered with IRQs\n");

	return 0;

remove_gpiochip:
	dev_info(&pdev->dev, "Remove gpiochip\n");
	gpiochip_remove(&plgpio->chip);
unprepare_clk:
	if (!IS_ERR(plgpio->clk))
		clk_unprepare(plgpio->clk);

	return ret;
}