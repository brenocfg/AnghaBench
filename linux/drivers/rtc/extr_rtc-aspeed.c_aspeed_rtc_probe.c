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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct aspeed_rtc {TYPE_1__* rtc_dev; TYPE_1__* base; } ;
struct TYPE_6__ {long long range_max; int /*<<< orphan*/  range_min; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_1900 ; 
 int /*<<< orphan*/  aspeed_rtc_ops ; 
 TYPE_1__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct aspeed_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct aspeed_rtc*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int aspeed_rtc_probe(struct platform_device *pdev)
{
	struct aspeed_rtc *rtc;
	struct resource *res;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rtc->base))
		return PTR_ERR(rtc->base);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc_dev))
		return PTR_ERR(rtc->rtc_dev);

	platform_set_drvdata(pdev, rtc);

	rtc->rtc_dev->ops = &aspeed_rtc_ops;
	rtc->rtc_dev->range_min = RTC_TIMESTAMP_BEGIN_1900;
	rtc->rtc_dev->range_max = 38814989399LL; /* 3199-12-31 23:59:59 */

	return rtc_register_device(rtc->rtc_dev);
}