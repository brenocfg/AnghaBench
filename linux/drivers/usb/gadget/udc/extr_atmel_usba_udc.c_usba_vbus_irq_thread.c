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
struct usba_udc {int vbus_prev; int suspended; int /*<<< orphan*/  vbus_mutex; int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usba_start (struct usba_udc*) ; 
 int /*<<< orphan*/  usba_stop (struct usba_udc*) ; 
 int vbus_is_present (struct usba_udc*) ; 

__attribute__((used)) static irqreturn_t usba_vbus_irq_thread(int irq, void *devid)
{
	struct usba_udc *udc = devid;
	int vbus;

	/* debounce */
	udelay(10);

	mutex_lock(&udc->vbus_mutex);

	vbus = vbus_is_present(udc);
	if (vbus != udc->vbus_prev) {
		if (vbus) {
			usba_start(udc);
		} else {
			udc->suspended = false;
			usba_stop(udc);

			if (udc->driver->disconnect)
				udc->driver->disconnect(&udc->gadget);
		}
		udc->vbus_prev = vbus;
	}

	mutex_unlock(&udc->vbus_mutex);
	return IRQ_HANDLED;
}