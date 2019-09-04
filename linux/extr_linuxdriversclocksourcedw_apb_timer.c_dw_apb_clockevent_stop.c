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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct dw_apb_clock_event_device {int /*<<< orphan*/  ced; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dw_apb_clockevent_stop(struct dw_apb_clock_event_device *dw_ced)
{
	free_irq(dw_ced->timer.irq, &dw_ced->ced);
}