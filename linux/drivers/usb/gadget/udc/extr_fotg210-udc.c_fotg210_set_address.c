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
struct usb_ctrlrequest {int wValue; } ;
struct fotg210_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fotg210_request_error (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_cxdone (struct fotg210_udc*) ; 
 int /*<<< orphan*/  fotg210_set_dev_addr (struct fotg210_udc*,int) ; 

__attribute__((used)) static void fotg210_set_address(struct fotg210_udc *fotg210,
				struct usb_ctrlrequest *ctrl)
{
	if (ctrl->wValue >= 0x0100) {
		fotg210_request_error(fotg210);
	} else {
		fotg210_set_dev_addr(fotg210, ctrl->wValue);
		fotg210_set_cxdone(fotg210);
	}
}