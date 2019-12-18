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
struct ftm_rtc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ftm_clean_alarm (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_irq_acknowledge (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_irq_disable (struct ftm_rtc*) ; 

__attribute__((used)) static irqreturn_t ftm_rtc_alarm_interrupt(int irq, void *dev)
{
	struct ftm_rtc *rtc = dev;

	ftm_irq_acknowledge(rtc);
	ftm_irq_disable(rtc);
	ftm_clean_alarm(rtc);

	return IRQ_HANDLED;
}