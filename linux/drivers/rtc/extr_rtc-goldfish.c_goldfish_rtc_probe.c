#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct goldfish_rtc {scalar_t__ irq; TYPE_1__* rtc; TYPE_1__* base; } ;
struct TYPE_6__ {int range_max; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int NSEC_PER_SEC ; 
 int PTR_ERR (TYPE_1__*) ; 
 int U64_MAX ; 
 TYPE_1__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct goldfish_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct goldfish_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  goldfish_rtc_interrupt ; 
 int /*<<< orphan*/  goldfish_rtc_ops ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct goldfish_rtc*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int goldfish_rtc_probe(struct platform_device *pdev)
{
	struct goldfish_rtc *rtcdrv;
	struct resource *r;
	int err;

	rtcdrv = devm_kzalloc(&pdev->dev, sizeof(*rtcdrv), GFP_KERNEL);
	if (!rtcdrv)
		return -ENOMEM;

	platform_set_drvdata(pdev, rtcdrv);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r)
		return -ENODEV;

	rtcdrv->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(rtcdrv->base))
		return -ENODEV;

	rtcdrv->irq = platform_get_irq(pdev, 0);
	if (rtcdrv->irq < 0)
		return -ENODEV;

	rtcdrv->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtcdrv->rtc))
		return PTR_ERR(rtcdrv->rtc);

	rtcdrv->rtc->ops = &goldfish_rtc_ops;
	rtcdrv->rtc->range_max = U64_MAX / NSEC_PER_SEC;

	err = devm_request_irq(&pdev->dev, rtcdrv->irq,
			       goldfish_rtc_interrupt,
			       0, pdev->name, rtcdrv);
	if (err)
		return err;

	return rtc_register_device(rtcdrv->rtc);
}