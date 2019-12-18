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
struct pl030_rtc {scalar_t__ base; } ;
struct amba_device {int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 scalar_t__ RTC_CR ; 
 struct pl030_rtc* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pl030_rtc*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pl030_remove(struct amba_device *dev)
{
	struct pl030_rtc *rtc = amba_get_drvdata(dev);

	writel(0, rtc->base + RTC_CR);

	free_irq(dev->irq[0], rtc);
	iounmap(rtc->base);
	amba_release_regions(dev);

	return 0;
}