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
struct pxa_rtc {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSR_RDALE1 ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtsr_clear_bits (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsr_set_bits (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	spin_lock_irq(&pxa_rtc->lock);

	if (enabled)
		rtsr_set_bits(pxa_rtc, RTSR_RDALE1);
	else
		rtsr_clear_bits(pxa_rtc, RTSR_RDALE1);

	spin_unlock_irq(&pxa_rtc->lock);
	return 0;
}