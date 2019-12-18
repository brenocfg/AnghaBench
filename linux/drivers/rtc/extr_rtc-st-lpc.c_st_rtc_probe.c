#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct st_rtc {TYPE_1__* clk; TYPE_1__* rtc_dev; int /*<<< orphan*/  clkrate; int /*<<< orphan*/  irq; TYPE_1__* ioaddr; int /*<<< orphan*/  lock; } ;
struct resource {int dummy; } ;
struct TYPE_18__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 scalar_t__ ST_LPC_MODE_RTC ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (TYPE_1__*) ; 
 TYPE_1__* clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (TYPE_1__*) ; 
 int /*<<< orphan*/  clk_prepare_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_3__*,int) ; 
 TYPE_1__* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct st_rtc* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct st_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_3__*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct st_rtc*) ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_rtc_handler ; 
 int /*<<< orphan*/  st_rtc_ops ; 

__attribute__((used)) static int st_rtc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct st_rtc *rtc;
	struct resource *res;
	uint32_t mode;
	int ret = 0;

	ret = of_property_read_u32(np, "st,lpc-mode", &mode);
	if (ret) {
		dev_err(&pdev->dev, "An LPC mode must be provided\n");
		return -EINVAL;
	}

	/* LPC can either run as a Clocksource or in RTC or WDT mode */
	if (mode != ST_LPC_MODE_RTC)
		return -ENODEV;

	rtc = devm_kzalloc(&pdev->dev, sizeof(struct st_rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc_dev))
		return PTR_ERR(rtc->rtc_dev);

	spin_lock_init(&rtc->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rtc->ioaddr))
		return PTR_ERR(rtc->ioaddr);

	rtc->irq = irq_of_parse_and_map(np, 0);
	if (!rtc->irq) {
		dev_err(&pdev->dev, "IRQ missing or invalid\n");
		return -EINVAL;
	}

	ret = devm_request_irq(&pdev->dev, rtc->irq, st_rtc_handler, 0,
			       pdev->name, rtc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq %i\n", rtc->irq);
		return ret;
	}

	enable_irq_wake(rtc->irq);
	disable_irq(rtc->irq);

	rtc->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(rtc->clk)) {
		dev_err(&pdev->dev, "Unable to request clock\n");
		return PTR_ERR(rtc->clk);
	}

	clk_prepare_enable(rtc->clk);

	rtc->clkrate = clk_get_rate(rtc->clk);
	if (!rtc->clkrate) {
		dev_err(&pdev->dev, "Unable to fetch clock rate\n");
		return -EINVAL;
	}

	device_set_wakeup_capable(&pdev->dev, 1);

	platform_set_drvdata(pdev, rtc);

	rtc->rtc_dev->ops = &st_rtc_ops;
	rtc->rtc_dev->range_max = U64_MAX;
	do_div(rtc->rtc_dev->range_max, rtc->clkrate);

	ret = rtc_register_device(rtc->rtc_dev);
	if (ret) {
		clk_disable_unprepare(rtc->clk);
		return ret;
	}

	return 0;
}