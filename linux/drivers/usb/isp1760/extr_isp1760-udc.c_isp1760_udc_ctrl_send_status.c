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
struct isp1760_udc {int /*<<< orphan*/  ep0_state; } ;
struct isp1760_ep {struct isp1760_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CTRLFUNC ; 
 int DC_ENDPIDX (int /*<<< orphan*/ ) ; 
 int DC_EPDIR ; 
 int /*<<< orphan*/  DC_EPINDEX ; 
 int DC_STATUS ; 
 int /*<<< orphan*/  ISP1760_CTRL_SETUP ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  isp1760_udc_write (struct isp1760_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isp1760_udc_ctrl_send_status(struct isp1760_ep *ep, int dir)
{
	struct isp1760_udc *udc = ep->udc;

	/*
	 * Proceed to the status stage. The status stage data packet flows in
	 * the direction opposite to the data stage data packets, we thus need
	 * to select the OUT/IN endpoint for IN/OUT transfers.
	 */
	isp1760_udc_write(udc, DC_EPINDEX, DC_ENDPIDX(0) |
			  (dir == USB_DIR_IN ? 0 : DC_EPDIR));
	isp1760_udc_write(udc, DC_CTRLFUNC, DC_STATUS);

	/*
	 * The hardware will terminate the request automatically and go back to
	 * the setup stage without notifying us.
	 */
	udc->ep0_state = ISP1760_CTRL_SETUP;
}