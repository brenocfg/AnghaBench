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
typedef  int /*<<< orphan*/  u32 ;
struct xusb_udc {scalar_t__ addr; int /*<<< orphan*/  (* write_fn ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_fn ) (scalar_t__) ;struct xusb_ep* ep; } ;
struct xusb_ep {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  XUSB_EP_CFG_STALL_MASK ; 
 size_t XUSB_EP_NUMBER_ZERO ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xudc_ep0_stall(struct xusb_udc *udc)
{
	u32 epcfgreg;
	struct xusb_ep *ep0 = &udc->ep[XUSB_EP_NUMBER_ZERO];

	epcfgreg = udc->read_fn(udc->addr + ep0->offset);
	epcfgreg |= XUSB_EP_CFG_STALL_MASK;
	udc->write_fn(udc->addr, ep0->offset, epcfgreg);
}