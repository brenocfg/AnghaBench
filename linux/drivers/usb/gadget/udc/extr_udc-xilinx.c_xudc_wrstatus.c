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
typedef  int u32 ;
struct xusb_udc {int (* read_fn ) (scalar_t__) ;scalar_t__ addr; int /*<<< orphan*/  (* write_fn ) (scalar_t__,scalar_t__,int) ;struct xusb_ep* ep; } ;
struct xusb_ep {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ XUSB_BUFFREADY_OFFSET ; 
 scalar_t__ XUSB_EP_BUF0COUNT_OFFSET ; 
 int XUSB_EP_CFG_DATA_TOGGLE_MASK ; 
 size_t XUSB_EP_NUMBER_ZERO ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void xudc_wrstatus(struct xusb_udc *udc)
{
	struct xusb_ep *ep0 = &udc->ep[XUSB_EP_NUMBER_ZERO];
	u32 epcfgreg;

	epcfgreg = udc->read_fn(udc->addr + ep0->offset)|
				XUSB_EP_CFG_DATA_TOGGLE_MASK;
	udc->write_fn(udc->addr, ep0->offset, epcfgreg);
	udc->write_fn(udc->addr, ep0->offset + XUSB_EP_BUF0COUNT_OFFSET, 0);
	udc->write_fn(udc->addr, XUSB_BUFFREADY_OFFSET, 1);
}