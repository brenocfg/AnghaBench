#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  notifier_call; } ;
struct brcmstb_waketmr {scalar_t__ irq; TYPE_2__* clk; TYPE_1__ reboot_notifier; TYPE_2__* rtc; void* rate; TYPE_2__* base; struct device* dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 void* BRCMSTB_WKTMR_DEFAULT_FREQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  brcmstb_waketmr_irq ; 
 int /*<<< orphan*/  brcmstb_waketmr_ops ; 
 int /*<<< orphan*/  brcmstb_waketmr_reboot ; 
 int /*<<< orphan*/  clk_disable_unprepare (TYPE_2__*) ; 
 void* clk_get_rate (TYPE_2__*) ; 
 int clk_prepare_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 int /*<<< orphan*/  device_wakeup_enable (struct device*) ; 
 TYPE_2__* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 TYPE_2__* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct brcmstb_waketmr* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct brcmstb_waketmr*) ; 
 TYPE_2__* devm_rtc_allocate_device (struct device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct brcmstb_waketmr*) ; 
 int /*<<< orphan*/  register_reboot_notifier (TYPE_1__*) ; 
 int rtc_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (TYPE_1__*) ; 

__attribute__((used)) static int brcmstb_waketmr_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct brcmstb_waketmr *timer;
	struct resource *res;
	int ret;

	timer = devm_kzalloc(dev, sizeof(*timer), GFP_KERNEL);
	if (!timer)
		return -ENOMEM;

	platform_set_drvdata(pdev, timer);
	timer->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	timer->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(timer->base))
		return PTR_ERR(timer->base);

	timer->rtc = devm_rtc_allocate_device(dev);
	if (IS_ERR(timer->rtc))
		return PTR_ERR(timer->rtc);

	/*
	 * Set wakeup capability before requesting wakeup interrupt, so we can
	 * process boot-time "wakeups" (e.g., from S5 soft-off)
	 */
	device_set_wakeup_capable(dev, true);
	device_wakeup_enable(dev);

	timer->irq = platform_get_irq(pdev, 0);
	if (timer->irq < 0)
		return -ENODEV;

	timer->clk = devm_clk_get(dev, NULL);
	if (!IS_ERR(timer->clk)) {
		ret = clk_prepare_enable(timer->clk);
		if (ret)
			return ret;
		timer->rate = clk_get_rate(timer->clk);
		if (!timer->rate)
			timer->rate = BRCMSTB_WKTMR_DEFAULT_FREQ;
	} else {
		timer->rate = BRCMSTB_WKTMR_DEFAULT_FREQ;
		timer->clk = NULL;
	}

	ret = devm_request_irq(dev, timer->irq, brcmstb_waketmr_irq, 0,
			       "brcmstb-waketimer", timer);
	if (ret < 0)
		goto err_clk;

	timer->reboot_notifier.notifier_call = brcmstb_waketmr_reboot;
	register_reboot_notifier(&timer->reboot_notifier);

	timer->rtc->ops = &brcmstb_waketmr_ops;
	timer->rtc->range_max = U32_MAX;

	ret = rtc_register_device(timer->rtc);
	if (ret)
		goto err_notifier;

	dev_info(dev, "registered, with irq %d\n", timer->irq);

	return 0;

err_notifier:
	unregister_reboot_notifier(&timer->reboot_notifier);

err_clk:
	if (timer->clk)
		clk_disable_unprepare(timer->clk);

	return ret;
}