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
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {scalar_t__ dir_in; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN_INT_BFRDY ; 
 int /*<<< orphan*/  USB3_PN_INT_ENA ; 
 int /*<<< orphan*/  USB3_PN_READ ; 
 int /*<<< orphan*/  USB3_PN_WRITE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct renesas_usb3_ep* usb3_get_ep (struct renesas_usb3*,int) ; 
 struct renesas_usb3_request* usb3_get_request (struct renesas_usb3_ep*) ; 
 scalar_t__ usb3_pn_change (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_read_pipe (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_request_done_pipen (struct renesas_usb3*,struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write_pipe (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_irq_epc_pipen_bfrdy(struct renesas_usb3 *usb3, int num)
{
	struct renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, num);
	struct renesas_usb3_request *usb3_req = usb3_get_request(usb3_ep);
	bool done = false;

	if (!usb3_req)
		return;

	spin_lock(&usb3->lock);
	if (usb3_pn_change(usb3, num))
		goto out;

	if (usb3_ep->dir_in) {
		/* Do not stop the IN pipe here to detect LSTTR interrupt */
		if (!usb3_write_pipe(usb3_ep, usb3_req, USB3_PN_WRITE))
			usb3_clear_bit(usb3, PN_INT_BFRDY, USB3_PN_INT_ENA);
	} else {
		if (!usb3_read_pipe(usb3_ep, usb3_req, USB3_PN_READ))
			done = true;
	}

out:
	/* need to unlock because usb3_request_done_pipen() locks it */
	spin_unlock(&usb3->lock);

	if (done)
		usb3_request_done_pipen(usb3, usb3_ep, usb3_req, 0);
}