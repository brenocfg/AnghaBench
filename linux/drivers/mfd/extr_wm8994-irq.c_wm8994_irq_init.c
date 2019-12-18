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
struct wm8994_pdata {long irq_flags; int /*<<< orphan*/  irq_gpio; } ;
struct wm8994 {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_data; scalar_t__ irq_base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  edge_irq; struct wm8994_pdata pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_IN ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 unsigned long IRQF_TRIGGER_HIGH ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  WM8994_INTERRUPT_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_to_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct wm8994*) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,scalar_t__,unsigned long,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,char*,struct wm8994*) ; 
 int /*<<< orphan*/  wm8994_edge_irq ; 
 int /*<<< orphan*/  wm8994_edge_irq_ops ; 
 int /*<<< orphan*/  wm8994_irq_chip ; 
 int /*<<< orphan*/  wm8994_reg_write (struct wm8994*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wm8994_irq_init(struct wm8994 *wm8994)
{
	int ret;
	unsigned long irqflags;
	struct wm8994_pdata *pdata = &wm8994->pdata;

	if (!wm8994->irq) {
		dev_warn(wm8994->dev,
			 "No interrupt specified, no interrupts\n");
		wm8994->irq_base = 0;
		return 0;
	}

	/* select user or default irq flags */
	irqflags = IRQF_TRIGGER_HIGH | IRQF_ONESHOT;
	if (pdata->irq_flags)
		irqflags = pdata->irq_flags;

	/* use a GPIO for edge triggered controllers */
	if (irqflags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) {
		if (gpio_to_irq(pdata->irq_gpio) != wm8994->irq) {
			dev_warn(wm8994->dev, "IRQ %d is not GPIO %d (%d)\n",
				 wm8994->irq, pdata->irq_gpio,
				 gpio_to_irq(pdata->irq_gpio));
			wm8994->irq = gpio_to_irq(pdata->irq_gpio);
		}

		ret = devm_gpio_request_one(wm8994->dev, pdata->irq_gpio,
					    GPIOF_IN, "WM8994 IRQ");

		if (ret != 0) {
			dev_err(wm8994->dev, "Failed to get IRQ GPIO: %d\n",
				ret);
			return ret;
		}

		wm8994->edge_irq = irq_domain_add_linear(NULL, 1,
							 &wm8994_edge_irq_ops,
							 wm8994);

		ret = regmap_add_irq_chip(wm8994->regmap,
					  irq_create_mapping(wm8994->edge_irq,
							     0),
					  IRQF_ONESHOT,
					  wm8994->irq_base, &wm8994_irq_chip,
					  &wm8994->irq_data);
		if (ret != 0) {
			dev_err(wm8994->dev, "Failed to get IRQ: %d\n",
				ret);
			return ret;
		}

		ret = request_threaded_irq(wm8994->irq,
					   NULL, wm8994_edge_irq,
					   irqflags,
					   "WM8994 edge", wm8994);
	} else {
		ret = regmap_add_irq_chip(wm8994->regmap, wm8994->irq,
					  irqflags,
					  wm8994->irq_base, &wm8994_irq_chip,
					  &wm8994->irq_data);
	}

	if (ret != 0) {
		dev_err(wm8994->dev, "Failed to register IRQ chip: %d\n", ret);
		return ret;
	}

	/* Enable top level interrupt if it was masked */
	wm8994_reg_write(wm8994, WM8994_INTERRUPT_CONTROL, 0);

	return 0;
}