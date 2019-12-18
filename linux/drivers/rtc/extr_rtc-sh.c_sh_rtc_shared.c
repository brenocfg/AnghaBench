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
struct sh_rtc {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int __sh_rtc_alarm (struct sh_rtc*) ; 
 int __sh_rtc_interrupt (struct sh_rtc*) ; 
 int __sh_rtc_periodic (struct sh_rtc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_rtc_shared(int irq, void *dev_id)
{
	struct sh_rtc *rtc = dev_id;
	int ret;

	spin_lock(&rtc->lock);
	ret = __sh_rtc_interrupt(rtc);
	ret |= __sh_rtc_alarm(rtc);
	ret |= __sh_rtc_periodic(rtc);
	spin_unlock(&rtc->lock);

	return IRQ_RETVAL(ret);
}