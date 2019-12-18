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
struct rtc_device {unsigned long long range_max; int /*<<< orphan*/  max_user_freq; int /*<<< orphan*/ * ops; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int num_resources; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ECMPHREG ; 
 int /*<<< orphan*/  ECMPLREG ; 
 int /*<<< orphan*/  ECMPMREG ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  MAX_PERIODIC_RATE ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  RTCL1HREG ; 
 int /*<<< orphan*/  RTCL1LREG ; 
 scalar_t__ aie_irq ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct platform_device*) ; 
 struct rtc_device* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  elapsedtime_interrupt ; 
 scalar_t__ pie_irq ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/ * rtc1_base ; 
 int /*<<< orphan*/  rtc1_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtc2_base ; 
 int /*<<< orphan*/  rtc_lock ; 
 int rtc_register_device (struct rtc_device*) ; 
 int /*<<< orphan*/  rtclong1_interrupt ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vr41xx_rtc_ops ; 

__attribute__((used)) static int rtc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct rtc_device *rtc;
	int retval;

	if (pdev->num_resources != 4)
		return -EBUSY;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EBUSY;

	rtc1_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!rtc1_base)
		return -EBUSY;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res) {
		retval = -EBUSY;
		goto err_rtc1_iounmap;
	}

	rtc2_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!rtc2_base) {
		retval = -EBUSY;
		goto err_rtc1_iounmap;
	}

	rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc)) {
		retval = PTR_ERR(rtc);
		goto err_iounmap_all;
	}

	rtc->ops = &vr41xx_rtc_ops;

	/* 48-bit counter at 32.768 kHz */
	rtc->range_max = (1ULL << 33) - 1;
	rtc->max_user_freq = MAX_PERIODIC_RATE;

	spin_lock_irq(&rtc_lock);

	rtc1_write(ECMPLREG, 0);
	rtc1_write(ECMPMREG, 0);
	rtc1_write(ECMPHREG, 0);
	rtc1_write(RTCL1LREG, 0);
	rtc1_write(RTCL1HREG, 0);

	spin_unlock_irq(&rtc_lock);

	aie_irq = platform_get_irq(pdev, 0);
	if (aie_irq <= 0) {
		retval = -EBUSY;
		goto err_iounmap_all;
	}

	retval = devm_request_irq(&pdev->dev, aie_irq, elapsedtime_interrupt, 0,
				"elapsed_time", pdev);
	if (retval < 0)
		goto err_iounmap_all;

	pie_irq = platform_get_irq(pdev, 1);
	if (pie_irq <= 0) {
		retval = -EBUSY;
		goto err_iounmap_all;
	}

	retval = devm_request_irq(&pdev->dev, pie_irq, rtclong1_interrupt, 0,
				"rtclong1", pdev);
	if (retval < 0)
		goto err_iounmap_all;

	platform_set_drvdata(pdev, rtc);

	disable_irq(aie_irq);
	disable_irq(pie_irq);

	dev_info(&pdev->dev, "Real Time Clock of NEC VR4100 series\n");

	retval = rtc_register_device(rtc);
	if (retval)
		goto err_iounmap_all;

	return 0;

err_iounmap_all:
	rtc2_base = NULL;

err_rtc1_iounmap:
	rtc1_base = NULL;

	return retval;
}