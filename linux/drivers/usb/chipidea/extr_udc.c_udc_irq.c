#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ speed; int /*<<< orphan*/  state; } ;
struct ci_hdrc {int suspended; int /*<<< orphan*/  lock; TYPE_3__ gadget; TYPE_2__* driver; int /*<<< orphan*/  resume_state; TYPE_1__* platdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* suspend ) (TYPE_3__*) ;int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int CI_HDRC_REGS_SHARED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OP_USBMODE ; 
 int /*<<< orphan*/  USBMODE_CM ; 
 scalar_t__ USBMODE_CM_DC ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  USB_STATE_SUSPENDED ; 
 int USBi_PCI ; 
 int USBi_SLI ; 
 int USBi_UI ; 
 int USBi_URI ; 
 scalar_t__ hw_port_is_high_speed (struct ci_hdrc*) ; 
 scalar_t__ hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hw_test_and_clear_intr_active (struct ci_hdrc*) ; 
 int /*<<< orphan*/  isr_reset_handler (struct ci_hdrc*) ; 
 int /*<<< orphan*/  isr_tr_complete_handler (struct ci_hdrc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_gadget_set_state (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t udc_irq(struct ci_hdrc *ci)
{
	irqreturn_t retval;
	u32 intr;

	if (ci == NULL)
		return IRQ_HANDLED;

	spin_lock(&ci->lock);

	if (ci->platdata->flags & CI_HDRC_REGS_SHARED) {
		if (hw_read(ci, OP_USBMODE, USBMODE_CM) !=
				USBMODE_CM_DC) {
			spin_unlock(&ci->lock);
			return IRQ_NONE;
		}
	}
	intr = hw_test_and_clear_intr_active(ci);

	if (intr) {
		/* order defines priority - do NOT change it */
		if (USBi_URI & intr)
			isr_reset_handler(ci);

		if (USBi_PCI & intr) {
			ci->gadget.speed = hw_port_is_high_speed(ci) ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
			if (ci->suspended) {
				if (ci->driver->resume) {
					spin_unlock(&ci->lock);
					ci->driver->resume(&ci->gadget);
					spin_lock(&ci->lock);
				}
				ci->suspended = 0;
				usb_gadget_set_state(&ci->gadget,
						ci->resume_state);
			}
		}

		if (USBi_UI  & intr)
			isr_tr_complete_handler(ci);

		if ((USBi_SLI & intr) && !(ci->suspended)) {
			ci->suspended = 1;
			ci->resume_state = ci->gadget.state;
			if (ci->gadget.speed != USB_SPEED_UNKNOWN &&
			    ci->driver->suspend) {
				spin_unlock(&ci->lock);
				ci->driver->suspend(&ci->gadget);
				spin_lock(&ci->lock);
			}
			usb_gadget_set_state(&ci->gadget,
					USB_STATE_SUSPENDED);
		}
		retval = IRQ_HANDLED;
	} else {
		retval = IRQ_NONE;
	}
	spin_unlock(&ci->lock);

	return retval;
}