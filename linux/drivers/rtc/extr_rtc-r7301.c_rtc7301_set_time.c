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
struct rtc7301_priv {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rtc7301_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc7301_select_bank (struct rtc7301_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc7301_start (struct rtc7301_priv*) ; 
 int /*<<< orphan*/  rtc7301_stop (struct rtc7301_priv*) ; 
 int /*<<< orphan*/  rtc7301_write_time (struct rtc7301_priv*,struct rtc_time*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtc7301_set_time(struct device *dev, struct rtc_time *tm)
{
	struct rtc7301_priv *priv = dev_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_stop(priv);
	udelay(300);
	rtc7301_select_bank(priv, 0);
	rtc7301_write_time(priv, tm, false);
	rtc7301_start(priv);

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}