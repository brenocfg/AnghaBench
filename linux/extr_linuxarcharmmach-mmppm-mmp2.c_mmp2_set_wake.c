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
struct irq_data {int irq; } ;

/* Variables and functions */
#define  IRQ_MMP2_MMC2 131 
#define  IRQ_MMP2_PMIC 130 
#define  IRQ_MMP2_RTC 129 
#define  IRQ_MMP2_RTC_ALARM 128 
 int /*<<< orphan*/  MPMU_WUCRM_PJ ; 
 unsigned long MPMU_WUCRM_PJ_RTC_ALARM ; 
 unsigned long MPMU_WUCRM_PJ_WAKEUP (int) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

int mmp2_set_wake(struct irq_data *d, unsigned int on)
{
	unsigned long data = 0;
	int irq = d->irq;

	/* enable wakeup sources */
	switch (irq) {
	case IRQ_MMP2_RTC:
	case IRQ_MMP2_RTC_ALARM:
		data = MPMU_WUCRM_PJ_WAKEUP(4) | MPMU_WUCRM_PJ_RTC_ALARM;
		break;
	case IRQ_MMP2_PMIC:
		data = MPMU_WUCRM_PJ_WAKEUP(7);
		break;
	case IRQ_MMP2_MMC2:
		/* mmc use WAKEUP2, same as GPIO wakeup source */
		data = MPMU_WUCRM_PJ_WAKEUP(2);
		break;
	}
	if (on) {
		if (data) {
			data |= __raw_readl(MPMU_WUCRM_PJ);
			__raw_writel(data, MPMU_WUCRM_PJ);
		}
	} else {
		if (data) {
			data = ~data & __raw_readl(MPMU_WUCRM_PJ);
			__raw_writel(data, MPMU_WUCRM_PJ);
		}
	}
	return 0;
}