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
struct sunxi_rtc_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sunxi_rtc_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sunxi_rtc_setaie (unsigned int,struct sunxi_rtc_dev*) ; 

__attribute__((used)) static int sunxi_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct sunxi_rtc_dev *chip = dev_get_drvdata(dev);

	if (!enabled)
		sunxi_rtc_setaie(enabled, chip);

	return 0;
}