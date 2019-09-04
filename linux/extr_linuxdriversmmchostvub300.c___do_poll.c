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
struct vub300_mmc_host {int usb_timed_out; int /*<<< orphan*/  command_res_urb; int /*<<< orphan*/  command_out_urb; scalar_t__ usb_transport_fail; int /*<<< orphan*/  irqpoll_complete; int /*<<< orphan*/  inactivity_timer; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  __vub300_irqpoll_response (struct vub300_mmc_host*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  send_irqpoll (struct vub300_mmc_host*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __do_poll(struct vub300_mmc_host *vub300)
{
	/* cmd_mutex is held by vub300_pollwork_thread */
	unsigned long commretval;
	mod_timer(&vub300->inactivity_timer, jiffies + HZ);
	init_completion(&vub300->irqpoll_complete);
	send_irqpoll(vub300);
	commretval = wait_for_completion_timeout(&vub300->irqpoll_complete,
						 msecs_to_jiffies(500));
	if (vub300->usb_transport_fail) {
		/* no need to do anything */
	} else if (commretval == 0) {
		vub300->usb_timed_out = 1;
		usb_kill_urb(vub300->command_out_urb);
		usb_kill_urb(vub300->command_res_urb);
	} else { /* commretval > 0 */
		__vub300_irqpoll_response(vub300);
	}
}