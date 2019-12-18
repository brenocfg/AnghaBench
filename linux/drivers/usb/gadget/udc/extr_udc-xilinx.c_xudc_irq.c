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
typedef  int u8 ;
typedef  int u32 ;
struct xusb_udc {int (* read_fn ) (scalar_t__) ;int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  (* write_fn ) (scalar_t__,scalar_t__,int) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ XUSB_IER_OFFSET ; 
 int XUSB_STATUS_EP0_BUFF1_COMP_MASK ; 
 int XUSB_STATUS_EP1_BUFF1_COMP_MASK ; 
 int XUSB_STATUS_EP1_BUFF2_COMP_MASK ; 
 int XUSB_STATUS_INTR_BUFF_COMP_ALL_MASK ; 
 int XUSB_STATUS_INTR_EVENT_MASK ; 
 scalar_t__ XUSB_STATUS_OFFSET ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int) ; 
 int stub3 (scalar_t__) ; 
 int stub4 (scalar_t__) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  xudc_ctrl_ep_handler (struct xusb_udc*,int) ; 
 int /*<<< orphan*/  xudc_nonctrl_ep_handler (struct xusb_udc*,int,int) ; 
 int /*<<< orphan*/  xudc_startup_handler (struct xusb_udc*,int) ; 

__attribute__((used)) static irqreturn_t xudc_irq(int irq, void *_udc)
{
	struct xusb_udc *udc = _udc;
	u32 intrstatus;
	u32 ier;
	u8 index;
	u32 bufintr;
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * Event interrupts are level sensitive hence first disable
	 * IER, read ISR and figure out active interrupts.
	 */
	ier = udc->read_fn(udc->addr + XUSB_IER_OFFSET);
	ier &= ~XUSB_STATUS_INTR_EVENT_MASK;
	udc->write_fn(udc->addr, XUSB_IER_OFFSET, ier);

	/* Read the Interrupt Status Register.*/
	intrstatus = udc->read_fn(udc->addr + XUSB_STATUS_OFFSET);

	/* Call the handler for the event interrupt.*/
	if (intrstatus & XUSB_STATUS_INTR_EVENT_MASK) {
		/*
		 * Check if there is any action to be done for :
		 * - USB Reset received {XUSB_STATUS_RESET_MASK}
		 * - USB Suspend received {XUSB_STATUS_SUSPEND_MASK}
		 * - USB Resume received {XUSB_STATUS_RESUME_MASK}
		 * - USB Disconnect received {XUSB_STATUS_DISCONNECT_MASK}
		 */
		xudc_startup_handler(udc, intrstatus);
	}

	/* Check the buffer completion interrupts */
	if (intrstatus & XUSB_STATUS_INTR_BUFF_COMP_ALL_MASK) {
		/* Enable Reset, Suspend, Resume and Disconnect  */
		ier = udc->read_fn(udc->addr + XUSB_IER_OFFSET);
		ier |= XUSB_STATUS_INTR_EVENT_MASK;
		udc->write_fn(udc->addr, XUSB_IER_OFFSET, ier);

		if (intrstatus & XUSB_STATUS_EP0_BUFF1_COMP_MASK)
			xudc_ctrl_ep_handler(udc, intrstatus);

		for (index = 1; index < 8; index++) {
			bufintr = ((intrstatus &
				  (XUSB_STATUS_EP1_BUFF1_COMP_MASK <<
				  (index - 1))) || (intrstatus &
				  (XUSB_STATUS_EP1_BUFF2_COMP_MASK <<
				  (index - 1))));
			if (bufintr) {
				xudc_nonctrl_ep_handler(udc, index,
							intrstatus);
			}
		}
	}

	spin_unlock_irqrestore(&udc->lock, flags);
	return IRQ_HANDLED;
}