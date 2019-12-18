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

/* Variables and functions */
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xb_waitq ; 
 scalar_t__ xenbus_irq ; 

void xb_deinit_comms(void)
{
	unbind_from_irqhandler(xenbus_irq, &xb_waitq);
	xenbus_irq = 0;
}