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
struct usb_gadget_driver {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct pxa_udc {struct usb_gadget_driver* driver; int /*<<< orphan*/  dev; int /*<<< orphan*/  gadget; TYPE_1__* transceiver; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ should_enable_udc (struct pxa_udc*) ; 
 struct pxa_udc* to_pxa (struct usb_gadget*) ; 
 int /*<<< orphan*/  udc_enable (struct pxa_udc*) ; 

__attribute__((used)) static int pxa27x_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct pxa_udc *udc = to_pxa(g);
	int retval;

	/* first hook up the driver ... */
	udc->driver = driver;

	if (!IS_ERR_OR_NULL(udc->transceiver)) {
		retval = otg_set_peripheral(udc->transceiver->otg,
						&udc->gadget);
		if (retval) {
			dev_err(udc->dev, "can't bind to transceiver\n");
			goto fail;
		}
	}

	if (should_enable_udc(udc))
		udc_enable(udc);
	return 0;

fail:
	udc->driver = NULL;
	return retval;
}