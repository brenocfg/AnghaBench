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
struct timer_list {int dummy; } ;
struct musb {int /*<<< orphan*/  lock; TYPE_2__* xceiv; int /*<<< orphan*/  is_active; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
#define  OTG_STATE_A_SUSPEND 130 
#define  OTG_STATE_A_WAIT_BCON 129 
 int OTG_STATE_A_WAIT_VFALL ; 
 int OTG_STATE_B_PERIPHERAL ; 
#define  OTG_STATE_B_WAIT_ACON 128 
 struct musb* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct musb* musb ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,...) ; 
 int /*<<< orphan*/  musb_g_disconnect (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_set_vbus (struct musb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static void musb_otg_timer_func(struct timer_list *t)
{
	struct musb	*musb = from_timer(musb, t, otg_timer);
	unsigned long	flags;

	spin_lock_irqsave(&musb->lock, flags);
	switch (musb->xceiv->otg->state) {
	case OTG_STATE_B_WAIT_ACON:
		musb_dbg(musb,
			"HNP: b_wait_acon timeout; back to b_peripheral");
		musb_g_disconnect(musb);
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		musb->is_active = 0;
		break;
	case OTG_STATE_A_SUSPEND:
	case OTG_STATE_A_WAIT_BCON:
		musb_dbg(musb, "HNP: %s timeout",
			usb_otg_state_string(musb->xceiv->otg->state));
		musb_platform_set_vbus(musb, 0);
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VFALL;
		break;
	default:
		musb_dbg(musb, "HNP: Unhandled mode %s",
			usb_otg_state_string(musb->xceiv->otg->state));
	}
	spin_unlock_irqrestore(&musb->lock, flags);
}