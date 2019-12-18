#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  otg; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dc_clk; int /*<<< orphan*/ * driver; int /*<<< orphan*/  lock; TYPE_4__* transceiver; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_4__*) ; 
 scalar_t__ machine_without_vbus_sense () ; 
 int /*<<< orphan*/  omap_udc_enable_clock (int) ; 
 int /*<<< orphan*/  omap_vbus_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullup_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* udc ; 
 int /*<<< orphan*/  udc_quiesce (TYPE_1__*) ; 

__attribute__((used)) static int omap_udc_stop(struct usb_gadget *g)
{
	unsigned long	flags;

	if (udc->dc_clk != NULL)
		omap_udc_enable_clock(1);

	if (machine_without_vbus_sense())
		omap_vbus_session(&udc->gadget, 0);

	if (!IS_ERR_OR_NULL(udc->transceiver))
		(void) otg_set_peripheral(udc->transceiver->otg, NULL);
	else
		pullup_disable(udc);

	spin_lock_irqsave(&udc->lock, flags);
	udc_quiesce(udc);
	spin_unlock_irqrestore(&udc->lock, flags);

	udc->driver = NULL;

	if (udc->dc_clk != NULL)
		omap_udc_enable_clock(0);

	return 0;
}