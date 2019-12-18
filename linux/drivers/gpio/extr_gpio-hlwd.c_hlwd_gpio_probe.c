#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct gpio_irq_chip {int num_parents; int* parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; TYPE_1__* chip; } ;
struct TYPE_13__ {int ngpio; struct gpio_irq_chip irq; } ;
struct TYPE_11__ {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  name; } ;
struct hlwd_gpio {scalar_t__ irq; TYPE_5__ gpioc; TYPE_1__ irqc; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGPIOF_BIG_ENDIAN_BYTE_ORDER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HW_GPIOB_DIR ; 
 scalar_t__ HW_GPIOB_IN ; 
 scalar_t__ HW_GPIOB_INTFLAG ; 
 scalar_t__ HW_GPIOB_INTMASK ; 
 scalar_t__ HW_GPIOB_OUT ; 
 scalar_t__ HW_GPIO_OWNER ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int bgpio_init (TYPE_5__*,TYPE_2__*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_5__*,struct hlwd_gpio*) ; 
 int* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct hlwd_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  hlwd_gpio_irq_enable ; 
 int /*<<< orphan*/  hlwd_gpio_irq_mask ; 
 int /*<<< orphan*/  hlwd_gpio_irq_set_type ; 
 int /*<<< orphan*/  hlwd_gpio_irq_unmask ; 
 int /*<<< orphan*/  hlwd_gpio_irqhandler ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hlwd_gpio_probe(struct platform_device *pdev)
{
	struct hlwd_gpio *hlwd;
	u32 ngpios;
	int res;

	hlwd = devm_kzalloc(&pdev->dev, sizeof(*hlwd), GFP_KERNEL);
	if (!hlwd)
		return -ENOMEM;

	hlwd->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hlwd->regs))
		return PTR_ERR(hlwd->regs);

	/*
	 * Claim all GPIOs using the OWNER register. This will not work on
	 * systems where the AHBPROT memory firewall hasn't been configured to
	 * permit PPC access to HW_GPIO_*.
	 *
	 * Note that this has to happen before bgpio_init reads the
	 * HW_GPIOB_OUT and HW_GPIOB_DIR, because otherwise it reads the wrong
	 * values.
	 */
	iowrite32be(0xffffffff, hlwd->regs + HW_GPIO_OWNER);

	res = bgpio_init(&hlwd->gpioc, &pdev->dev, 4,
			hlwd->regs + HW_GPIOB_IN, hlwd->regs + HW_GPIOB_OUT,
			NULL, hlwd->regs + HW_GPIOB_DIR, NULL,
			BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	if (res < 0) {
		dev_warn(&pdev->dev, "bgpio_init failed: %d\n", res);
		return res;
	}

	res = of_property_read_u32(pdev->dev.of_node, "ngpios", &ngpios);
	if (res)
		ngpios = 32;
	hlwd->gpioc.ngpio = ngpios;

	/* Mask and ack all interrupts */
	iowrite32be(0, hlwd->regs + HW_GPIOB_INTMASK);
	iowrite32be(0xffffffff, hlwd->regs + HW_GPIOB_INTFLAG);

	/*
	 * If this GPIO controller is not marked as an interrupt controller in
	 * the DT, skip interrupt support.
	 */
	if (of_property_read_bool(pdev->dev.of_node, "interrupt-controller")) {
		struct gpio_irq_chip *girq;

		hlwd->irq = platform_get_irq(pdev, 0);
		if (hlwd->irq < 0) {
			dev_info(&pdev->dev, "platform_get_irq returned %d\n",
				 hlwd->irq);
			return hlwd->irq;
		}

		hlwd->irqc.name = dev_name(&pdev->dev);
		hlwd->irqc.irq_mask = hlwd_gpio_irq_mask;
		hlwd->irqc.irq_unmask = hlwd_gpio_irq_unmask;
		hlwd->irqc.irq_enable = hlwd_gpio_irq_enable;
		hlwd->irqc.irq_set_type = hlwd_gpio_irq_set_type;

		girq = &hlwd->gpioc.irq;
		girq->chip = &hlwd->irqc;
		girq->parent_handler = hlwd_gpio_irqhandler;
		girq->num_parents = 1;
		girq->parents = devm_kcalloc(&pdev->dev, 1,
					     sizeof(*girq->parents),
					     GFP_KERNEL);
		if (!girq->parents)
			return -ENOMEM;
		girq->parents[0] = hlwd->irq;
		girq->default_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;
	}

	return devm_gpiochip_add_data(&pdev->dev, &hlwd->gpioc, hlwd);
}