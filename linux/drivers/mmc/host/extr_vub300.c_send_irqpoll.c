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
struct TYPE_3__ {int header_size; int header_type; int command_type; int poll_timeout_lsb; int poll_timeout_msb; scalar_t__ port_number; } ;
struct TYPE_4__ {TYPE_1__ poll; } ;
struct vub300_mmc_host {int usb_transport_fail; int /*<<< orphan*/  irqpoll_complete; int /*<<< orphan*/  command_out_urb; TYPE_2__ cmnd; int /*<<< orphan*/  cmnd_out_ep; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int firmware_irqpoll_timeout ; 
 int /*<<< orphan*/  irqpoll_out_completed ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,struct vub300_mmc_host*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vub300_queue_poll_work (struct vub300_mmc_host*,int) ; 

__attribute__((used)) static void send_irqpoll(struct vub300_mmc_host *vub300)
{
	/* cmd_mutex is held by vub300_pollwork_thread */
	int retval;
	int timeout = 0xFFFF & (0x0001FFFF - firmware_irqpoll_timeout);
	vub300->cmnd.poll.header_size = 22;
	vub300->cmnd.poll.header_type = 1;
	vub300->cmnd.poll.port_number = 0;
	vub300->cmnd.poll.command_type = 2;
	vub300->cmnd.poll.poll_timeout_lsb = 0xFF & (unsigned)timeout;
	vub300->cmnd.poll.poll_timeout_msb = 0xFF & (unsigned)(timeout >> 8);
	usb_fill_bulk_urb(vub300->command_out_urb, vub300->udev,
			  usb_sndbulkpipe(vub300->udev, vub300->cmnd_out_ep)
			  , &vub300->cmnd, sizeof(vub300->cmnd)
			  , irqpoll_out_completed, vub300);
	retval = usb_submit_urb(vub300->command_out_urb, GFP_KERNEL);
	if (0 > retval) {
		vub300->usb_transport_fail = retval;
		vub300_queue_poll_work(vub300, 1);
		complete(&vub300->irqpoll_complete);
		return;
	} else {
		return;
	}
}