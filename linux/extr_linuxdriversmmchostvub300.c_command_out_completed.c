#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vub300_mmc_host {int /*<<< orphan*/  command_complete; TYPE_1__* command_res_urb; int /*<<< orphan*/  resp; int /*<<< orphan*/  udev; int /*<<< orphan*/  cmnd_res_ep; } ;
struct urb {scalar_t__ status; scalar_t__ context; } ;
struct TYPE_3__ {scalar_t__ actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  command_res_completed ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct vub300_mmc_host*) ; 
 unsigned int usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void command_out_completed(struct urb *urb)
{				/* urb completion handler - hardirq */
	struct vub300_mmc_host *vub300 = (struct vub300_mmc_host *)urb->context;
	if (urb->status) {
		complete(&vub300->command_complete);
	} else {
		int ret;
		unsigned int pipe =
			usb_rcvbulkpipe(vub300->udev, vub300->cmnd_res_ep);
		usb_fill_bulk_urb(vub300->command_res_urb, vub300->udev, pipe,
				  &vub300->resp, sizeof(vub300->resp),
				  command_res_completed, vub300);
		vub300->command_res_urb->actual_length = 0;
		ret = usb_submit_urb(vub300->command_res_urb, GFP_ATOMIC);
		if (ret == 0) {
			/*
			 * the urb completion handler will call
			 * our completion handler
			 */
		} else {
			/*
			 * and thus we only call it directly
			 * when it will not be called
			 */
			complete(&vub300->command_complete);
		}
	}
}