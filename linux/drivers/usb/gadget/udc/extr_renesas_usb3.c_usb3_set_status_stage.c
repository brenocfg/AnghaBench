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
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct renesas_usb3_request {TYPE_1__ req; } ;
struct renesas_usb3_ep {scalar_t__ dir_in; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_set_p0_con_for_ctrl_read_status (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_p0_con_for_ctrl_write_status (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_p0_con_for_no_data (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_set_status_stage(struct renesas_usb3_ep *usb3_ep,
				  struct renesas_usb3_request *usb3_req)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	if (usb3_ep->dir_in) {
		usb3_set_p0_con_for_ctrl_read_status(usb3);
	} else {
		if (!usb3_req->req.length)
			usb3_set_p0_con_for_no_data(usb3);
		else
			usb3_set_p0_con_for_ctrl_write_status(usb3);
	}
}