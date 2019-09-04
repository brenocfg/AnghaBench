#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  error_code; } ;
struct TYPE_7__ {int header_type; } ;
struct TYPE_10__ {TYPE_4__ error; TYPE_2__ common; } ;
struct vub300_mmc_host {int /*<<< orphan*/  command_complete; int /*<<< orphan*/  sg_request; TYPE_5__ resp; TYPE_3__* cmd; scalar_t__ urb; int /*<<< orphan*/  data; TYPE_1__* command_res_urb; } ;
struct urb {scalar_t__ status; scalar_t__ context; } ;
struct TYPE_8__ {void* error; } ;
struct TYPE_6__ {scalar_t__ actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_sg_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (scalar_t__) ; 
 void* vub300_response_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void command_res_completed(struct urb *urb)
{				/* urb completion handler - hardirq */
	struct vub300_mmc_host *vub300 = (struct vub300_mmc_host *)urb->context;
	if (urb->status) {
		/* we have to let the initiator handle the error */
	} else if (vub300->command_res_urb->actual_length == 0) {
		/*
		 * we have seen this happen once or twice and
		 * we suspect a buggy USB host controller
		 */
	} else if (!vub300->data) {
		/* this means that the command (typically CMD52) succeeded */
	} else if (vub300->resp.common.header_type != 0x02) {
		/*
		 * this is an error response from the VUB300 chip
		 * and we let the initiator handle it
		 */
	} else if (vub300->urb) {
		vub300->cmd->error =
			vub300_response_error(vub300->resp.error.error_code);
		usb_unlink_urb(vub300->urb);
	} else {
		vub300->cmd->error =
			vub300_response_error(vub300->resp.error.error_code);
		usb_sg_cancel(&vub300->sg_request);
	}
	complete(&vub300->command_complete);	/* got_response_in */
}