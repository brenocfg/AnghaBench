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

/* Variables and functions */
 int /*<<< orphan*/  USB3_P0_READ ; 
 int /*<<< orphan*/  USB3_P0_WRITE ; 
 int usb3_read_pipe (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_set_status_stage (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 
 int usb3_write_pipe (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_p0_xfer(struct renesas_usb3_ep *usb3_ep,
			 struct renesas_usb3_request *usb3_req)
{
	int ret;

	if (usb3_ep->dir_in)
		ret = usb3_write_pipe(usb3_ep, usb3_req, USB3_P0_WRITE);
	else
		ret = usb3_read_pipe(usb3_ep, usb3_req, USB3_P0_READ);

	if (!ret)
		usb3_set_status_stage(usb3_ep, usb3_req);
}