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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct zevio_timer {TYPE_1__ clkevt; scalar_t__ timer1; scalar_t__ interrupt_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CNTL_STOP_TIMER ; 
 scalar_t__ IO_CONTROL ; 
 scalar_t__ IO_INTR_ACK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int TIMER_INTR_MSK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t zevio_timer_interrupt(int irq, void *dev_id)
{
	struct zevio_timer *timer = dev_id;
	u32 intr;

	intr = readl(timer->interrupt_regs + IO_INTR_ACK);
	if (!(intr & TIMER_INTR_MSK))
		return IRQ_NONE;

	writel(TIMER_INTR_MSK, timer->interrupt_regs + IO_INTR_ACK);
	writel(CNTL_STOP_TIMER, timer->timer1 + IO_CONTROL);

	if (timer->clkevt.event_handler)
		timer->clkevt.event_handler(&timer->clkevt);

	return IRQ_HANDLED;
}