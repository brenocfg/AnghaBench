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
struct usb_hcd {TYPE_1__* driver; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_2__ {scalar_t__ (* irq ) (struct usb_hcd*) ;} ;

/* Variables and functions */
 scalar_t__ HCD_DEAD (struct usb_hcd*) ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ stub1 (struct usb_hcd*) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t usb_hcd_irq (int irq, void *__hcd)
{
	struct usb_hcd		*hcd = __hcd;
	irqreturn_t		rc;

	if (unlikely(HCD_DEAD(hcd) || !HCD_HW_ACCESSIBLE(hcd)))
		rc = IRQ_NONE;
	else if (hcd->driver->irq(hcd) == IRQ_NONE)
		rc = IRQ_NONE;
	else
		rc = IRQ_HANDLED;

	return rc;
}