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
struct isp1760_udc {int /*<<< orphan*/  isp; scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ADDRESS ; 
 int DC_CDBGMOD_ACK ; 
 int DC_DDBGMODIN_ACK ; 
 int DC_DDBGMODOUT_ACK_NYET ; 
 int DC_DEVEN ; 
 int DC_IEBRST ; 
 int DC_IEHS_STA ; 
 int DC_IEP0SETUP ; 
 int DC_IEPRXTX (int) ; 
 int DC_IERESM ; 
 int DC_IESUSP ; 
 int DC_IEVBUS ; 
 int /*<<< orphan*/  DC_INTCONF ; 
 int /*<<< orphan*/  DC_INTENABLE ; 
 int /*<<< orphan*/  isp1760_set_pullup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp1760_udc_write (struct isp1760_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isp1760_udc_init_hw(struct isp1760_udc *udc)
{
	/*
	 * The device controller currently shares its interrupt with the host
	 * controller, the DC_IRQ polarity and signaling mode are ignored. Set
	 * the to active-low level-triggered.
	 *
	 * Configure the control, in and out pipes to generate interrupts on
	 * ACK tokens only (and NYET for the out pipe). The default
	 * configuration also generates an interrupt on the first NACK token.
	 */
	isp1760_udc_write(udc, DC_INTCONF, DC_CDBGMOD_ACK | DC_DDBGMODIN_ACK |
			  DC_DDBGMODOUT_ACK_NYET);

	isp1760_udc_write(udc, DC_INTENABLE, DC_IEPRXTX(7) | DC_IEPRXTX(6) |
			  DC_IEPRXTX(5) | DC_IEPRXTX(4) | DC_IEPRXTX(3) |
			  DC_IEPRXTX(2) | DC_IEPRXTX(1) | DC_IEPRXTX(0) |
			  DC_IEP0SETUP | DC_IEVBUS | DC_IERESM | DC_IESUSP |
			  DC_IEHS_STA | DC_IEBRST);

	if (udc->connected)
		isp1760_set_pullup(udc->isp, true);

	isp1760_udc_write(udc, DC_ADDRESS, DC_DEVEN);
}