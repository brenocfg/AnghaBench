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
struct rtc_time {int dummy; } ;
struct mc13xxx_rtc {int valid; int /*<<< orphan*/  mc13xxx; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC13XXX_IRQ_RTCRST ; 
 int /*<<< orphan*/  MC13XXX_RTCDAY ; 
 int /*<<< orphan*/  MC13XXX_RTCTOD ; 
 int /*<<< orphan*/  MC13XXX_RTCTODA ; 
 unsigned int SEC_PER_DAY ; 
 struct mc13xxx_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int div_s64_rem (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int mc13xxx_irq_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc13xxx_irq_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int mc13xxx_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int mc13xxx_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (struct rtc_time*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mc13xxx_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct mc13xxx_rtc *priv = dev_get_drvdata(dev);
	unsigned int seconds, days;
	unsigned int alarmseconds;
	int ret;

	days = div_s64_rem(rtc_tm_to_time64(tm), SEC_PER_DAY, &seconds);

	mc13xxx_lock(priv->mc13xxx);

	/*
	 * temporarily invalidate alarm to prevent triggering it when the day is
	 * already updated while the time isn't yet.
	 */
	ret = mc13xxx_reg_read(priv->mc13xxx, MC13XXX_RTCTODA, &alarmseconds);
	if (unlikely(ret))
		goto out;

	if (alarmseconds < SEC_PER_DAY) {
		ret = mc13xxx_reg_write(priv->mc13xxx,
				MC13XXX_RTCTODA, 0x1ffff);
		if (unlikely(ret))
			goto out;
	}

	/*
	 * write seconds=0 to prevent a day switch between writing days
	 * and seconds below
	 */
	ret = mc13xxx_reg_write(priv->mc13xxx, MC13XXX_RTCTOD, 0);
	if (unlikely(ret))
		goto out;

	ret = mc13xxx_reg_write(priv->mc13xxx, MC13XXX_RTCDAY, days);
	if (unlikely(ret))
		goto out;

	ret = mc13xxx_reg_write(priv->mc13xxx, MC13XXX_RTCTOD, seconds);
	if (unlikely(ret))
		goto out;

	/* restore alarm */
	if (alarmseconds < SEC_PER_DAY) {
		ret = mc13xxx_reg_write(priv->mc13xxx,
				MC13XXX_RTCTODA, alarmseconds);
		if (unlikely(ret))
			goto out;
	}

	if (!priv->valid) {
		ret = mc13xxx_irq_ack(priv->mc13xxx, MC13XXX_IRQ_RTCRST);
		if (unlikely(ret))
			goto out;

		ret = mc13xxx_irq_unmask(priv->mc13xxx, MC13XXX_IRQ_RTCRST);
	}

out:
	priv->valid = !ret;

	mc13xxx_unlock(priv->mc13xxx);

	return ret;
}