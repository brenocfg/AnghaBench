#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device_id {int driver_data; } ;
struct TYPE_19__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct of_device_id {scalar_t__ data; } ;
struct jz4740_rtc {int type; scalar_t__ irq; int reset_pin_assert_time; int min_wakeup_pin_assert_time; TYPE_1__* rtc; int /*<<< orphan*/  lock; TYPE_1__* clk; TYPE_1__* base; } ;
struct device_node {int dummy; } ;
typedef  enum jz4740_rtc_type { ____Placeholder_jz4740_rtc_type } jz4740_rtc_type ;
struct TYPE_18__ {int /*<<< orphan*/  range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 TYPE_2__* dev_for_power_off ; 
 int dev_pm_set_wake_irq (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_2__*,int) ; 
 TYPE_1__* devm_clk_get (TYPE_2__*,char*) ; 
 TYPE_1__* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct jz4740_rtc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4740_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_2__*) ; 
 int /*<<< orphan*/  jz4740_rtc_irq ; 
 int /*<<< orphan*/  jz4740_rtc_of_match ; 
 int /*<<< orphan*/  jz4740_rtc_ops ; 
 scalar_t__ jz4740_rtc_power_off ; 
 scalar_t__ of_device_is_system_power_controller (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4740_rtc*) ; 
 scalar_t__ pm_power_off ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4740_rtc_probe(struct platform_device *pdev)
{
	int ret;
	struct jz4740_rtc *rtc;
	struct resource *mem;
	const struct platform_device_id *id = platform_get_device_id(pdev);
	const struct of_device_id *of_id = of_match_device(
			jz4740_rtc_of_match, &pdev->dev);
	struct device_node *np = pdev->dev.of_node;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	if (of_id)
		rtc->type = (enum jz4740_rtc_type)of_id->data;
	else
		rtc->type = id->driver_data;

	rtc->irq = platform_get_irq(pdev, 0);
	if (rtc->irq < 0)
		return -ENOENT;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(rtc->base))
		return PTR_ERR(rtc->base);

	rtc->clk = devm_clk_get(&pdev->dev, "rtc");
	if (IS_ERR(rtc->clk)) {
		dev_err(&pdev->dev, "Failed to get RTC clock\n");
		return PTR_ERR(rtc->clk);
	}

	spin_lock_init(&rtc->lock);

	platform_set_drvdata(pdev, rtc);

	device_init_wakeup(&pdev->dev, 1);

	ret = dev_pm_set_wake_irq(&pdev->dev, rtc->irq);
	if (ret) {
		dev_err(&pdev->dev, "Failed to set wake irq: %d\n", ret);
		return ret;
	}

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc)) {
		ret = PTR_ERR(rtc->rtc);
		dev_err(&pdev->dev, "Failed to allocate rtc device: %d\n", ret);
		return ret;
	}

	rtc->rtc->ops = &jz4740_rtc_ops;
	rtc->rtc->range_max = U32_MAX;

	ret = rtc_register_device(rtc->rtc);
	if (ret)
		return ret;

	ret = devm_request_irq(&pdev->dev, rtc->irq, jz4740_rtc_irq, 0,
				pdev->name, rtc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request rtc irq: %d\n", ret);
		return ret;
	}

	if (np && of_device_is_system_power_controller(np)) {
		if (!pm_power_off) {
			/* Default: 60ms */
			rtc->reset_pin_assert_time = 60;
			of_property_read_u32(np, "reset-pin-assert-time-ms",
					     &rtc->reset_pin_assert_time);

			/* Default: 100ms */
			rtc->min_wakeup_pin_assert_time = 100;
			of_property_read_u32(np,
					     "min-wakeup-pin-assert-time-ms",
					     &rtc->min_wakeup_pin_assert_time);

			dev_for_power_off = &pdev->dev;
			pm_power_off = jz4740_rtc_power_off;
		} else {
			dev_warn(&pdev->dev,
				 "Poweroff handler already present!\n");
		}
	}

	return 0;
}