#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct musb {int /*<<< orphan*/  controller; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  lock; int /*<<< orphan*/ * gadget_driver; scalar_t__ is_active; TYPE_1__* xceiv; int /*<<< orphan*/  g; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {TYPE_2__* otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 struct musb* gadget_to_musb (struct usb_gadget*) ; 
 int /*<<< orphan*/  musb_gadget_vbus_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_hnp_stop (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_try_idle (struct musb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_stop (struct musb*) ; 
 int /*<<< orphan*/  otg_set_peripheral (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int musb_gadget_stop(struct usb_gadget *g)
{
	struct musb	*musb = gadget_to_musb(g);
	unsigned long	flags;

	pm_runtime_get_sync(musb->controller);

	/*
	 * REVISIT always use otg_set_peripheral() here too;
	 * this needs to shut down the OTG engine.
	 */

	spin_lock_irqsave(&musb->lock, flags);

	musb_hnp_stop(musb);

	(void) musb_gadget_vbus_draw(&musb->g, 0);

	musb->xceiv->otg->state = OTG_STATE_UNDEFINED;
	musb_stop(musb);
	otg_set_peripheral(musb->xceiv->otg, NULL);

	musb->is_active = 0;
	musb->gadget_driver = NULL;
	musb_platform_try_idle(musb, 0);
	spin_unlock_irqrestore(&musb->lock, flags);

	/*
	 * FIXME we need to be able to register another
	 * gadget driver here and have everything work;
	 * that currently misbehaves.
	 */

	/* Force check of devctl register for PM runtime */
	schedule_delayed_work(&musb->irq_work, 0);

	pm_runtime_mark_last_busy(musb->controller);
	pm_runtime_put_autosuspend(musb->controller);

	return 0;
}