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
struct usb_gadget {int dummy; } ;
struct pxa_udc {int /*<<< orphan*/  transceiver; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct pxa_udc* to_gadget_udc (struct usb_gadget*) ; 
 int usb_phy_set_power (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pxa_udc_vbus_draw(struct usb_gadget *_gadget, unsigned mA)
{
	struct pxa_udc *udc;

	udc = to_gadget_udc(_gadget);
	if (!IS_ERR_OR_NULL(udc->transceiver))
		return usb_phy_set_power(udc->transceiver, mA);
	return -EOPNOTSUPP;
}