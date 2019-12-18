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
struct vub300_mmc_host {int /*<<< orphan*/  irqpoll_complete; scalar_t__ usb_transport_fail; } ;
struct urb {scalar_t__ status; scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void irqpoll_res_completed(struct urb *urb)
{				/* urb completion handler - hardirq */
	struct vub300_mmc_host *vub300 = (struct vub300_mmc_host *)urb->context;
	if (urb->status)
		vub300->usb_transport_fail = urb->status;
	complete(&vub300->irqpoll_complete);
}