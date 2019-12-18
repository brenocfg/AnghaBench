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
struct mc13xxx_rtc {int /*<<< orphan*/  mc13xxx; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC13XXX_IRQ_TODA ; 
 struct mc13xxx_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int mc13xxx_rtc_irq_enable_unlocked (struct device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mc13xxx_rtc_alarm_irq_enable(struct device *dev,
					unsigned int enabled)
{
	struct mc13xxx_rtc *priv = dev_get_drvdata(dev);
	int ret;

	mc13xxx_lock(priv->mc13xxx);

	ret = mc13xxx_rtc_irq_enable_unlocked(dev, enabled, MC13XXX_IRQ_TODA);

	mc13xxx_unlock(priv->mc13xxx);

	return ret;
}