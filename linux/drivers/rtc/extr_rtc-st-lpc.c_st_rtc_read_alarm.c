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
struct st_rtc {int /*<<< orphan*/  lock; int /*<<< orphan*/  alarm; } ;
struct rtc_wkalrm {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct st_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (struct rtc_wkalrm*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int st_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct st_rtc *rtc = dev_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&rtc->lock, flags);

	memcpy(wkalrm, &rtc->alarm, sizeof(struct rtc_wkalrm));

	spin_unlock_irqrestore(&rtc->lock, flags);

	return 0;
}