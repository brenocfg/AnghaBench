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
struct dw_apb_clock_event_device {int /*<<< orphan*/  timer; int /*<<< orphan*/  ced; } ;

/* Variables and functions */
 int /*<<< orphan*/  APBTMR_N_CONTROL ; 
 int /*<<< orphan*/  apbt_enable_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apbt_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockevents_register_device (int /*<<< orphan*/ *) ; 

void dw_apb_clockevent_register(struct dw_apb_clock_event_device *dw_ced)
{
	apbt_writel(&dw_ced->timer, 0, APBTMR_N_CONTROL);
	clockevents_register_device(&dw_ced->ced);
	apbt_enable_int(&dw_ced->timer);
}