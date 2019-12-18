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
typedef  int u16 ;
struct qe_udc {int /*<<< orphan*/  lock; TYPE_1__* usb_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  usb_usber; int /*<<< orphan*/  usb_usbmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int USB_E_BSY_MASK ; 
 int USB_E_IDLE_MASK ; 
 int USB_E_RESET_MASK ; 
 int USB_E_RXB_MASK ; 
 int USB_E_TXB_MASK ; 
 int USB_E_TXE_MASK ; 
 int /*<<< orphan*/  bsy_irq (struct qe_udc*) ; 
 int /*<<< orphan*/  idle_irq (struct qe_udc*) ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset_irq (struct qe_udc*) ; 
 int /*<<< orphan*/  rx_irq (struct qe_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_irq (struct qe_udc*) ; 
 int /*<<< orphan*/  txe_irq (struct qe_udc*) ; 

__attribute__((used)) static irqreturn_t qe_udc_irq(int irq, void *_udc)
{
	struct qe_udc *udc = (struct qe_udc *)_udc;
	u16 irq_src;
	irqreturn_t status = IRQ_NONE;
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	irq_src = in_be16(&udc->usb_regs->usb_usber) &
		in_be16(&udc->usb_regs->usb_usbmr);
	/* Clear notification bits */
	out_be16(&udc->usb_regs->usb_usber, irq_src);
	/* USB Interrupt */
	if (irq_src & USB_E_IDLE_MASK) {
		idle_irq(udc);
		irq_src &= ~USB_E_IDLE_MASK;
		status = IRQ_HANDLED;
	}

	if (irq_src & USB_E_TXB_MASK) {
		tx_irq(udc);
		irq_src &= ~USB_E_TXB_MASK;
		status = IRQ_HANDLED;
	}

	if (irq_src & USB_E_RXB_MASK) {
		rx_irq(udc);
		irq_src &= ~USB_E_RXB_MASK;
		status = IRQ_HANDLED;
	}

	if (irq_src & USB_E_RESET_MASK) {
		reset_irq(udc);
		irq_src &= ~USB_E_RESET_MASK;
		status = IRQ_HANDLED;
	}

	if (irq_src & USB_E_BSY_MASK) {
		bsy_irq(udc);
		irq_src &= ~USB_E_BSY_MASK;
		status = IRQ_HANDLED;
	}

	if (irq_src & USB_E_TXE_MASK) {
		txe_irq(udc);
		irq_src &= ~USB_E_TXE_MASK;
		status = IRQ_HANDLED;
	}

	spin_unlock_irqrestore(&udc->lock, flags);

	return status;
}