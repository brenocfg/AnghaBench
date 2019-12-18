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
struct vub300_mmc_host {int usb_timed_out; int /*<<< orphan*/  command_res_urb; int /*<<< orphan*/  command_out_urb; int /*<<< orphan*/  sg_request; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct vub300_mmc_host* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_transfer_timer ; 
 int /*<<< orphan*/  usb_sg_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 
 struct vub300_mmc_host* vub300 ; 

__attribute__((used)) static void vub300_sg_timed_out(struct timer_list *t)
{
	struct vub300_mmc_host *vub300 = from_timer(vub300, t,
						    sg_transfer_timer);
	vub300->usb_timed_out = 1;
	usb_sg_cancel(&vub300->sg_request);
	usb_unlink_urb(vub300->command_out_urb);
	usb_unlink_urb(vub300->command_res_urb);
}