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
struct lpc32xx_udc {int ep0state; struct lpc32xx_ep* ep; } ;
struct lpc32xx_ep {int /*<<< orphan*/  totalints; } ;

/* Variables and functions */
#define  DATA_OUT 129 
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  EP_OUT ; 
 int EP_SEL_EPN ; 
 int EP_SEL_F ; 
 int EP_SEL_ST ; 
 int EP_SEL_STP ; 
#define  WAIT_FOR_SETUP 128 
 int /*<<< orphan*/  nuke (struct lpc32xx_ep*,int /*<<< orphan*/ ) ; 
 int udc_clearep_getsts (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_clrstall_hwep (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_ep0_out_req (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  udc_handle_ep0_setup (struct lpc32xx_udc*) ; 

__attribute__((used)) static void udc_handle_ep0_out(struct lpc32xx_udc *udc)
{
	struct lpc32xx_ep *ep0 = &udc->ep[0];
	u32 epstatus;

	/* Clear EP interrupt */
	epstatus = udc_clearep_getsts(udc, EP_OUT);


#ifdef CONFIG_USB_GADGET_DEBUG_FILES
	ep0->totalints++;
#endif

	/* Stalled? */
	if (epstatus & EP_SEL_ST) {
		udc_clrstall_hwep(udc, EP_OUT);
		nuke(ep0, -ECONNABORTED);
		udc->ep0state = WAIT_FOR_SETUP;
		return;
	}

	/* A NAK may occur if a packet couldn't be received yet */
	if (epstatus & EP_SEL_EPN)
		return;
	/* Setup packet incoming? */
	if (epstatus & EP_SEL_STP) {
		nuke(ep0, 0);
		udc->ep0state = WAIT_FOR_SETUP;
	}

	/* Data available? */
	if (epstatus & EP_SEL_F)
		/* Handle based on current state */
		switch (udc->ep0state) {
		case WAIT_FOR_SETUP:
			udc_handle_ep0_setup(udc);
			break;

		case DATA_OUT:
			udc_ep0_out_req(udc);
			break;

		default:
			/* Unknown state for EP0 */
			nuke(ep0, -ECONNABORTED);
			udc->ep0state = WAIT_FOR_SETUP;
		}
}