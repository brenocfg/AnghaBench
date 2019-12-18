#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pl030_rtc {scalar_t__ base; TYPE_1__* rtc; } ;
struct amba_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct amba_device {int /*<<< orphan*/ * irq; TYPE_2__ res; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 scalar_t__ RTC_CR ; 
 scalar_t__ RTC_EOI ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int amba_request_regions (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct pl030_rtc*) ; 
 struct pl030_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pl030_rtc*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pl030_interrupt ; 
 int /*<<< orphan*/  pl030_ops ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pl030_rtc*) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int pl030_probe(struct amba_device *dev, const struct amba_id *id)
{
	struct pl030_rtc *rtc;
	int ret;

	ret = amba_request_regions(dev, NULL);
	if (ret)
		goto err_req;

	rtc = devm_kzalloc(&dev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc) {
		ret = -ENOMEM;
		goto err_rtc;
	}

	rtc->rtc = devm_rtc_allocate_device(&dev->dev);
	if (IS_ERR(rtc->rtc)) {
		ret = PTR_ERR(rtc->rtc);
		goto err_rtc;
	}

	rtc->rtc->ops = &pl030_ops;
	rtc->base = ioremap(dev->res.start, resource_size(&dev->res));
	if (!rtc->base) {
		ret = -ENOMEM;
		goto err_rtc;
	}

	__raw_writel(0, rtc->base + RTC_CR);
	__raw_writel(0, rtc->base + RTC_EOI);

	amba_set_drvdata(dev, rtc);

	ret = request_irq(dev->irq[0], pl030_interrupt, 0,
			  "rtc-pl030", rtc);
	if (ret)
		goto err_irq;

	ret = rtc_register_device(rtc->rtc);
	if (ret)
		goto err_reg;

	return 0;

 err_reg:
	free_irq(dev->irq[0], rtc);
 err_irq:
	iounmap(rtc->base);
 err_rtc:
	amba_release_regions(dev);
 err_req:
	return ret;
}