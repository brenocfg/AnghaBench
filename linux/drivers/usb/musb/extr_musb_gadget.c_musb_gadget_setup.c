#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {TYPE_4__ dev; scalar_t__ is_otg; int /*<<< orphan*/  name; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_speed; int /*<<< orphan*/ * ops; } ;
struct musb {TYPE_3__ g; int /*<<< orphan*/  controller; scalar_t__ is_active; int /*<<< orphan*/  gadget_work; TYPE_2__* xceiv; } ;
struct TYPE_6__ {TYPE_1__* otg; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB_DEV_MODE (struct musb*) ; 
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  device_unregister (TYPE_4__*) ; 
 int /*<<< orphan*/  musb_driver_name ; 
 int /*<<< orphan*/  musb_g_init_endpoints (struct musb*) ; 
 int /*<<< orphan*/  musb_gadget_operations ; 
 int /*<<< orphan*/  musb_gadget_work ; 
 int /*<<< orphan*/  musb_platform_try_idle (struct musb*,int /*<<< orphan*/ ) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ ,TYPE_3__*) ; 

int musb_gadget_setup(struct musb *musb)
{
	int status;

	/* REVISIT minor race:  if (erroneously) setting up two
	 * musb peripherals at the same time, only the bus lock
	 * is probably held.
	 */

	musb->g.ops = &musb_gadget_operations;
	musb->g.max_speed = USB_SPEED_HIGH;
	musb->g.speed = USB_SPEED_UNKNOWN;

	MUSB_DEV_MODE(musb);
	musb->xceiv->otg->state = OTG_STATE_B_IDLE;

	/* this "gadget" abstracts/virtualizes the controller */
	musb->g.name = musb_driver_name;
	/* don't support otg protocols */
	musb->g.is_otg = 0;
	INIT_DELAYED_WORK(&musb->gadget_work, musb_gadget_work);
	musb_g_init_endpoints(musb);

	musb->is_active = 0;
	musb_platform_try_idle(musb, 0);

	status = usb_add_gadget_udc(musb->controller, &musb->g);
	if (status)
		goto err;

	return 0;
err:
	musb->g.dev.parent = NULL;
	device_unregister(&musb->g.dev);
	return status;
}