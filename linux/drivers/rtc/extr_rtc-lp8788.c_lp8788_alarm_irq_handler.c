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
struct lp8788_rtc {int /*<<< orphan*/  rdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALARM_IRQ_FLAG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lp8788_alarm_irq_handler(int irq, void *ptr)
{
	struct lp8788_rtc *rtc = ptr;

	rtc_update_irq(rtc->rdev, 1, ALARM_IRQ_FLAG);
	return IRQ_HANDLED;
}