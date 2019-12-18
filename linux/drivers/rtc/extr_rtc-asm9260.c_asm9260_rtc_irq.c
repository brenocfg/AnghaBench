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
typedef  int /*<<< orphan*/  u32 ;
struct asm9260_rtc_priv {TYPE_1__* rtc; scalar_t__ iobase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ops_lock; } ;

/* Variables and functions */
 scalar_t__ HW_CIIR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_1__*,int,unsigned long) ; 

__attribute__((used)) static irqreturn_t asm9260_rtc_irq(int irq, void *dev_id)
{
	struct asm9260_rtc_priv *priv = dev_id;
	u32 isr;
	unsigned long events = 0;

	mutex_lock(&priv->rtc->ops_lock);
	isr = ioread32(priv->iobase + HW_CIIR);
	if (!isr) {
		mutex_unlock(&priv->rtc->ops_lock);
		return IRQ_NONE;
	}

	iowrite32(0, priv->iobase + HW_CIIR);
	mutex_unlock(&priv->rtc->ops_lock);

	events |= RTC_AF | RTC_IRQF;

	rtc_update_irq(priv->rtc, 1, events);

	return IRQ_HANDLED;
}