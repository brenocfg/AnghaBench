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
struct udc_usb_ep {scalar_t__ pxa_ep; } ;
struct pxa_udc {struct udc_usb_ep* udc_usb_ep; } ;

/* Variables and functions */
 int NR_USB_ENDPOINTS ; 
 scalar_t__ find_pxa_ep (struct pxa_udc*,struct udc_usb_ep*) ; 

__attribute__((used)) static void update_pxa_ep_matches(struct pxa_udc *udc)
{
	int i;
	struct udc_usb_ep *udc_usb_ep;

	for (i = 1; i < NR_USB_ENDPOINTS; i++) {
		udc_usb_ep = &udc->udc_usb_ep[i];
		if (udc_usb_ep->pxa_ep)
			udc_usb_ep->pxa_ep = find_pxa_ep(udc, udc_usb_ep);
	}
}