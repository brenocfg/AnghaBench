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
typedef  int u32 ;
struct sun6i_rtc_dev {int /*<<< orphan*/  alarm; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SUN6I_ALRM_EN_CNT_EN ; 
 scalar_t__ SUN6I_ALRM_IRQ_EN ; 
 scalar_t__ SUN6I_ALRM_IRQ_STA ; 
 struct sun6i_rtc_dev* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sun6i_rtc_getalarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct sun6i_rtc_dev *chip = dev_get_drvdata(dev);
	unsigned long flags;
	u32 alrm_st;
	u32 alrm_en;

	spin_lock_irqsave(&chip->lock, flags);
	alrm_en = readl(chip->base + SUN6I_ALRM_IRQ_EN);
	alrm_st = readl(chip->base + SUN6I_ALRM_IRQ_STA);
	spin_unlock_irqrestore(&chip->lock, flags);

	wkalrm->enabled = !!(alrm_en & SUN6I_ALRM_EN_CNT_EN);
	wkalrm->pending = !!(alrm_st & SUN6I_ALRM_EN_CNT_EN);
	rtc_time_to_tm(chip->alarm, &wkalrm->time);

	return 0;
}