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
typedef  scalar_t__ u8 ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ A20R_PT_TIM0_ACK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static irqreturn_t a20r_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *cd = dev_id;

	*(volatile u8 *)A20R_PT_TIM0_ACK = 0;
	wmb();

	cd->event_handler(cd);

	return IRQ_HANDLED;
}