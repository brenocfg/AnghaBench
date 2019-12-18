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
typedef  int u8 ;
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct rtc7301_priv {scalar_t__ irq; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTC7301_ALARM_CONTROL ; 
 int RTC7301_ALARM_CONTROL_AF ; 
 int RTC7301_ALARM_CONTROL_AIE ; 
 struct rtc7301_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc7301_get_time (struct rtc7301_priv*,int /*<<< orphan*/ *,int) ; 
 int rtc7301_read (struct rtc7301_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc7301_select_bank (struct rtc7301_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rtc7301_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct rtc7301_priv *priv = dev_get_drvdata(dev);
	unsigned long flags;
	u8 alrm_ctrl;

	if (priv->irq <= 0)
		return -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 1);
	rtc7301_get_time(priv, &alarm->time, true);

	alrm_ctrl = rtc7301_read(priv, RTC7301_ALARM_CONTROL);

	alarm->enabled = !!(alrm_ctrl & RTC7301_ALARM_CONTROL_AIE);
	alarm->pending = !!(alrm_ctrl & RTC7301_ALARM_CONTROL_AF);

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}