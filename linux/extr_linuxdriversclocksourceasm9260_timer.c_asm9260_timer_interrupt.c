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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_IR_MR0 ; 
 scalar_t__ HW_IR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_1__ priv ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t asm9260_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = dev_id;

	evt->event_handler(evt);

	writel_relaxed(BM_IR_MR0, priv.base + HW_IR);

	return IRQ_HANDLED;
}