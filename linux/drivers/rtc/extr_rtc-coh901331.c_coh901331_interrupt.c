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
struct coh901331_port {int /*<<< orphan*/  rtc; int /*<<< orphan*/  clk; scalar_t__ virtbase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ COH901331_IRQ_EVENT ; 
 scalar_t__ COH901331_IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTC_AF ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t coh901331_interrupt(int irq, void *data)
{
	struct coh901331_port *rtap = data;

	clk_enable(rtap->clk);
	/* Ack IRQ */
	writel(1, rtap->virtbase + COH901331_IRQ_EVENT);
	/*
	 * Disable the interrupt. This is necessary because
	 * the RTC lives on a lower-clocked line and will
	 * not release the IRQ line until after a few (slower)
	 * clock cycles. The interrupt will be re-enabled when
	 * a new alarm is set anyway.
	 */
	writel(0, rtap->virtbase + COH901331_IRQ_MASK);
	clk_disable(rtap->clk);

	/* Set alarm flag */
	rtc_update_irq(rtap->rtc, 1, RTC_AF);

	return IRQ_HANDLED;
}