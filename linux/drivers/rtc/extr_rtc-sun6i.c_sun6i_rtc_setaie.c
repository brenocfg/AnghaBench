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
typedef  int /*<<< orphan*/  u32 ;
struct sun6i_rtc_dev {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SUN6I_ALARM_CONFIG ; 
 int /*<<< orphan*/  SUN6I_ALARM_CONFIG_WAKEUP ; 
 scalar_t__ SUN6I_ALRM_EN ; 
 int /*<<< orphan*/  SUN6I_ALRM_EN_CNT_EN ; 
 scalar_t__ SUN6I_ALRM_IRQ_EN ; 
 int /*<<< orphan*/  SUN6I_ALRM_IRQ_EN_CNT_IRQ_EN ; 
 scalar_t__ SUN6I_ALRM_IRQ_STA ; 
 int /*<<< orphan*/  SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun6i_rtc_setaie(int to, struct sun6i_rtc_dev *chip)
{
	u32 alrm_val = 0;
	u32 alrm_irq_val = 0;
	u32 alrm_wake_val = 0;
	unsigned long flags;

	if (to) {
		alrm_val = SUN6I_ALRM_EN_CNT_EN;
		alrm_irq_val = SUN6I_ALRM_IRQ_EN_CNT_IRQ_EN;
		alrm_wake_val = SUN6I_ALARM_CONFIG_WAKEUP;
	} else {
		writel(SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND,
		       chip->base + SUN6I_ALRM_IRQ_STA);
	}

	spin_lock_irqsave(&chip->lock, flags);
	writel(alrm_val, chip->base + SUN6I_ALRM_EN);
	writel(alrm_irq_val, chip->base + SUN6I_ALRM_IRQ_EN);
	writel(alrm_wake_val, chip->base + SUN6I_ALARM_CONFIG);
	spin_unlock_irqrestore(&chip->lock, flags);
}