#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct platform_device {int dummy; } ;
struct mutex {int dummy; } ;
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct mutex ops_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long RTC_AF ; 
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_AIE ; 
 int RTC_CTRL_B_PAU_MASK ; 
 int RTC_CTRL_B_PIE ; 
 int RTC_CTRL_B_UIE ; 
 int /*<<< orphan*/  RTC_CTRL_C ; 
 int RTC_CTRL_C_AF ; 
 int RTC_CTRL_C_IRQF ; 
 int RTC_CTRL_C_PF ; 
 int RTC_CTRL_C_UF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_PF ; 
 unsigned long RTC_UF ; 
 int /*<<< orphan*/  ds1685_rtc_extended_irq (struct ds1685_priv*,struct platform_device*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 struct ds1685_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_1__*,int,unsigned long) ; 
 int stub1 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
ds1685_rtc_irq_handler(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct ds1685_priv *rtc = platform_get_drvdata(pdev);
	struct mutex *rtc_mutex;
	u8 ctrlb, ctrlc;
	unsigned long events = 0;
	u8 num_irqs = 0;

	/* Abort early if the device isn't ready yet (i.e., DEBUG_SHIRQ). */
	if (unlikely(!rtc))
		return IRQ_HANDLED;

	rtc_mutex = &rtc->dev->ops_lock;
	mutex_lock(rtc_mutex);

	/* Ctrlb holds the interrupt-enable bits and ctrlc the flag bits. */
	ctrlb = rtc->read(rtc, RTC_CTRL_B);
	ctrlc = rtc->read(rtc, RTC_CTRL_C);

	/* Is the IRQF bit set? */
	if (likely(ctrlc & RTC_CTRL_C_IRQF)) {
		/*
		 * We need to determine if it was one of the standard
		 * events: PF, AF, or UF.  If so, we handle them and
		 * update the RTC core.
		 */
		if (likely(ctrlc & RTC_CTRL_B_PAU_MASK)) {
			events = RTC_IRQF;

			/* Check for a periodic interrupt. */
			if ((ctrlb & RTC_CTRL_B_PIE) &&
			    (ctrlc & RTC_CTRL_C_PF)) {
				events |= RTC_PF;
				num_irqs++;
			}

			/* Check for an alarm interrupt. */
			if ((ctrlb & RTC_CTRL_B_AIE) &&
			    (ctrlc & RTC_CTRL_C_AF)) {
				events |= RTC_AF;
				num_irqs++;
			}

			/* Check for an update interrupt. */
			if ((ctrlb & RTC_CTRL_B_UIE) &&
			    (ctrlc & RTC_CTRL_C_UF)) {
				events |= RTC_UF;
				num_irqs++;
			}
		} else {
			/*
			 * One of the "extended" interrupts was received that
			 * is not recognized by the RTC core.
			 */
			ds1685_rtc_extended_irq(rtc, pdev);
		}
	}
	rtc_update_irq(rtc->dev, num_irqs, events);
	mutex_unlock(rtc_mutex);

	return events ? IRQ_HANDLED : IRQ_NONE;
}