#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int /*<<< orphan*/  ep0; } ;
struct TYPE_4__ {TYPE_1__* req; int /*<<< orphan*/ * serial; } ;
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 TYPE_2__ dbgp ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void dbgp_unbind(struct usb_gadget *gadget)
{
#ifdef CONFIG_USB_G_DBGP_SERIAL
	kfree(dbgp.serial);
	dbgp.serial = NULL;
#endif
	if (dbgp.req) {
		kfree(dbgp.req->buf);
		usb_ep_free_request(gadget->ep0, dbgp.req);
		dbgp.req = NULL;
	}
}