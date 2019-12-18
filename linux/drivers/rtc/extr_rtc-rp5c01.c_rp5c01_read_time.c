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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_wday; int tm_mon; int tm_year; } ;
struct rp5c01_priv {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP5C01_10_DAY ; 
 int /*<<< orphan*/  RP5C01_10_HOUR ; 
 int /*<<< orphan*/  RP5C01_10_MINUTE ; 
 int /*<<< orphan*/  RP5C01_10_MONTH ; 
 int /*<<< orphan*/  RP5C01_10_SECOND ; 
 int /*<<< orphan*/  RP5C01_10_YEAR ; 
 int /*<<< orphan*/  RP5C01_1_DAY ; 
 int /*<<< orphan*/  RP5C01_1_HOUR ; 
 int /*<<< orphan*/  RP5C01_1_MINUTE ; 
 int /*<<< orphan*/  RP5C01_1_MONTH ; 
 int /*<<< orphan*/  RP5C01_1_SECOND ; 
 int /*<<< orphan*/  RP5C01_1_YEAR ; 
 int /*<<< orphan*/  RP5C01_DAY_OF_WEEK ; 
 struct rp5c01_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rp5c01_lock (struct rp5c01_priv*) ; 
 int rp5c01_read (struct rp5c01_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp5c01_unlock (struct rp5c01_priv*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rp5c01_read_time(struct device *dev, struct rtc_time *tm)
{
	struct rp5c01_priv *priv = dev_get_drvdata(dev);

	spin_lock_irq(&priv->lock);
	rp5c01_lock(priv);

	tm->tm_sec  = rp5c01_read(priv, RP5C01_10_SECOND) * 10 +
		      rp5c01_read(priv, RP5C01_1_SECOND);
	tm->tm_min  = rp5c01_read(priv, RP5C01_10_MINUTE) * 10 +
		      rp5c01_read(priv, RP5C01_1_MINUTE);
	tm->tm_hour = rp5c01_read(priv, RP5C01_10_HOUR) * 10 +
		      rp5c01_read(priv, RP5C01_1_HOUR);
	tm->tm_mday = rp5c01_read(priv, RP5C01_10_DAY) * 10 +
		      rp5c01_read(priv, RP5C01_1_DAY);
	tm->tm_wday = rp5c01_read(priv, RP5C01_DAY_OF_WEEK);
	tm->tm_mon  = rp5c01_read(priv, RP5C01_10_MONTH) * 10 +
		      rp5c01_read(priv, RP5C01_1_MONTH) - 1;
	tm->tm_year = rp5c01_read(priv, RP5C01_10_YEAR) * 10 +
		      rp5c01_read(priv, RP5C01_1_YEAR);
	if (tm->tm_year <= 69)
		tm->tm_year += 100;

	rp5c01_unlock(priv);
	spin_unlock_irq(&priv->lock);

	return 0;
}