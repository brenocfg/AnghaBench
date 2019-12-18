#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct ftm_rtc {int alarm_freq; TYPE_1__* rtc_dev; int /*<<< orphan*/  big_endian; TYPE_1__* base; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ FIXED_FREQ_CLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 scalar_t__ MAX_FREQ_DIV ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 TYPE_1__* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct ftm_rtc* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ftm_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_3__*) ; 
 int /*<<< orphan*/  ftm_rtc_alarm_interrupt ; 
 int /*<<< orphan*/  ftm_rtc_ops ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ftm_rtc*) ; 
 int rtc_register_device (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ftm_rtc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct resource *r;
	int irq;
	int ret;
	struct ftm_rtc *rtc;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (unlikely(!rtc)) {
		dev_err(&pdev->dev, "cannot alloc memory for rtc\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, rtc);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc_dev))
		return PTR_ERR(rtc->rtc_dev);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r) {
		dev_err(&pdev->dev, "cannot get resource for rtc\n");
		return -ENODEV;
	}

	rtc->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(rtc->base)) {
		dev_err(&pdev->dev, "cannot ioremap resource for rtc\n");
		return PTR_ERR(rtc->base);
	}

	irq = irq_of_parse_and_map(np, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "unable to get IRQ from DT, %d\n", irq);
		return -EINVAL;
	}

	ret = devm_request_irq(&pdev->dev, irq, ftm_rtc_alarm_interrupt,
			       IRQF_NO_SUSPEND, dev_name(&pdev->dev), rtc);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to request irq\n");
		return ret;
	}

	rtc->big_endian = of_property_read_bool(np, "big-endian");
	rtc->alarm_freq = (u32)FIXED_FREQ_CLK / (u32)MAX_FREQ_DIV;
	rtc->rtc_dev->ops = &ftm_rtc_ops;

	device_init_wakeup(&pdev->dev, true);

	ret = rtc_register_device(rtc->rtc_dev);
	if (ret) {
		dev_err(&pdev->dev, "can't register rtc device\n");
		return ret;
	}

	return 0;
}