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
struct isp1760_udc {int connected; int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 struct isp1760_udc* gadget_to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  isp1760_set_pullup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isp1760_udc_pullup(struct usb_gadget *gadget, int is_on)
{
	struct isp1760_udc *udc = gadget_to_udc(gadget);

	isp1760_set_pullup(udc->isp, is_on);
	udc->connected = is_on;

	return 0;
}