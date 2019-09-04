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
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct oxnas_rps_timer {TYPE_1__ clkevent; scalar_t__ clkevt_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TIMER_CLRINT_REG ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t oxnas_rps_timer_irq(int irq, void *dev_id)
{
	struct oxnas_rps_timer *rps = dev_id;

	writel_relaxed(0, rps->clkevt_base + TIMER_CLRINT_REG);

	rps->clkevent.event_handler(&rps->clkevent);

	return IRQ_HANDLED;
}