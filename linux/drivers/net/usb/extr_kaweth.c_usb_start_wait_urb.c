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
struct usb_api_data {scalar_t__ done; int /*<<< orphan*/  wqh; } ;
struct urb {int status; int actual_length; TYPE_1__* dev; struct usb_api_data* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int usb_start_wait_urb(struct urb *urb, int timeout, int* actual_length)
{
	struct usb_api_data awd;
        int status;

        init_waitqueue_head(&awd.wqh);
        awd.done = 0;

        urb->context = &awd;
        status = usb_submit_urb(urb, GFP_ATOMIC);
        if (status) {
                // something went wrong
                usb_free_urb(urb);
                return status;
        }

	if (!wait_event_timeout(awd.wqh, awd.done, timeout)) {
                // timeout
                dev_warn(&urb->dev->dev, "usb_control/bulk_msg: timeout\n");
                usb_kill_urb(urb);  // remove urb safely
                status = -ETIMEDOUT;
        }
	else {
                status = urb->status;
	}

        if (actual_length) {
                *actual_length = urb->actual_length;
	}

        usb_free_urb(urb);
        return status;
}