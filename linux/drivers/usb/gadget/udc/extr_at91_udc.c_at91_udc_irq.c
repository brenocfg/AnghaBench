#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  speed; } ;
struct at91_udc {int suspended; int /*<<< orphan*/  lock; struct at91_ep* ep; TYPE_2__ gadget; TYPE_1__* driver; scalar_t__ addr; int /*<<< orphan*/  clocked; } ;
struct at91_ep {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* resume ) (TYPE_2__*) ;int /*<<< orphan*/  (* suspend ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_UDP_CSR (int /*<<< orphan*/ ) ; 
 int AT91_UDP_ENDBUSRES ; 
 int AT91_UDP_EP (int /*<<< orphan*/ ) ; 
 int AT91_UDP_EPEDS ; 
 int AT91_UDP_EPTYPE_CTRL ; 
 int /*<<< orphan*/  AT91_UDP_ICR ; 
 int /*<<< orphan*/  AT91_UDP_IDR ; 
 int /*<<< orphan*/  AT91_UDP_IER ; 
 int /*<<< orphan*/  AT91_UDP_IMR ; 
 int /*<<< orphan*/  AT91_UDP_ISR ; 
 int AT91_UDP_RXRSM ; 
 int AT91_UDP_RXSUSP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MINIMUS_INTERRUPTUS ; 
 int NUM_ENDPOINTS ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  VDBG (char*) ; 
 int at91_udp_read (struct at91_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_udp_write (struct at91_udc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_off (struct at91_udc*) ; 
 int /*<<< orphan*/  clk_on (struct at91_udc*) ; 
 int /*<<< orphan*/  handle_ep (struct at91_ep*) ; 
 int /*<<< orphan*/  handle_ep0 (struct at91_udc*) ; 
 int /*<<< orphan*/  reset_gadget (struct at91_udc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static irqreturn_t at91_udc_irq (int irq, void *_udc)
{
	struct at91_udc		*udc = _udc;
	u32			rescans = 5;
	int			disable_clock = 0;
	unsigned long		flags;

	spin_lock_irqsave(&udc->lock, flags);

	if (!udc->clocked) {
		clk_on(udc);
		disable_clock = 1;
	}

	while (rescans--) {
		u32 status;

		status = at91_udp_read(udc, AT91_UDP_ISR)
			& at91_udp_read(udc, AT91_UDP_IMR);
		if (!status)
			break;

		/* USB reset irq:  not maskable */
		if (status & AT91_UDP_ENDBUSRES) {
			at91_udp_write(udc, AT91_UDP_IDR, ~MINIMUS_INTERRUPTUS);
			at91_udp_write(udc, AT91_UDP_IER, MINIMUS_INTERRUPTUS);
			/* Atmel code clears this irq twice */
			at91_udp_write(udc, AT91_UDP_ICR, AT91_UDP_ENDBUSRES);
			at91_udp_write(udc, AT91_UDP_ICR, AT91_UDP_ENDBUSRES);
			VDBG("end bus reset\n");
			udc->addr = 0;
			reset_gadget(udc);

			/* enable ep0 */
			at91_udp_write(udc, AT91_UDP_CSR(0),
					AT91_UDP_EPEDS | AT91_UDP_EPTYPE_CTRL);
			udc->gadget.speed = USB_SPEED_FULL;
			udc->suspended = 0;
			at91_udp_write(udc, AT91_UDP_IER, AT91_UDP_EP(0));

			/*
			 * NOTE:  this driver keeps clocks off unless the
			 * USB host is present.  That saves power, but for
			 * boards that don't support VBUS detection, both
			 * clocks need to be active most of the time.
			 */

		/* host initiated suspend (3+ms bus idle) */
		} else if (status & AT91_UDP_RXSUSP) {
			at91_udp_write(udc, AT91_UDP_IDR, AT91_UDP_RXSUSP);
			at91_udp_write(udc, AT91_UDP_IER, AT91_UDP_RXRSM);
			at91_udp_write(udc, AT91_UDP_ICR, AT91_UDP_RXSUSP);
			/* VDBG("bus suspend\n"); */
			if (udc->suspended)
				continue;
			udc->suspended = 1;

			/*
			 * NOTE:  when suspending a VBUS-powered device, the
			 * gadget driver should switch into slow clock mode
			 * and then into standby to avoid drawing more than
			 * 500uA power (2500uA for some high-power configs).
			 */
			if (udc->driver && udc->driver->suspend) {
				spin_unlock(&udc->lock);
				udc->driver->suspend(&udc->gadget);
				spin_lock(&udc->lock);
			}

		/* host initiated resume */
		} else if (status & AT91_UDP_RXRSM) {
			at91_udp_write(udc, AT91_UDP_IDR, AT91_UDP_RXRSM);
			at91_udp_write(udc, AT91_UDP_IER, AT91_UDP_RXSUSP);
			at91_udp_write(udc, AT91_UDP_ICR, AT91_UDP_RXRSM);
			/* VDBG("bus resume\n"); */
			if (!udc->suspended)
				continue;
			udc->suspended = 0;

			/*
			 * NOTE:  for a VBUS-powered device, the gadget driver
			 * would normally want to switch out of slow clock
			 * mode into normal mode.
			 */
			if (udc->driver && udc->driver->resume) {
				spin_unlock(&udc->lock);
				udc->driver->resume(&udc->gadget);
				spin_lock(&udc->lock);
			}

		/* endpoint IRQs are cleared by handling them */
		} else {
			int		i;
			unsigned	mask = 1;
			struct at91_ep	*ep = &udc->ep[1];

			if (status & mask)
				handle_ep0(udc);
			for (i = 1; i < NUM_ENDPOINTS; i++) {
				mask <<= 1;
				if (status & mask)
					handle_ep(ep);
				ep++;
			}
		}
	}

	if (disable_clock)
		clk_off(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	return IRQ_HANDLED;
}