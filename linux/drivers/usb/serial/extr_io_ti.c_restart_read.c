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
struct urb {int dummy; } ;
struct edgeport_port {scalar_t__ ep_read_urb_state; int /*<<< orphan*/  ep_lock; int /*<<< orphan*/  shadow_mcr; TYPE_1__* port; } ;
struct TYPE_2__ {struct urb* read_urb; } ;

/* Variables and functions */
 scalar_t__ EDGE_READ_URB_RUNNING ; 
 scalar_t__ EDGE_READ_URB_STOPPED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MCR_RTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int restart_read(struct edgeport_port *edge_port)
{
	struct urb *urb;
	int status = 0;
	unsigned long flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	if (edge_port->ep_read_urb_state == EDGE_READ_URB_STOPPED) {
		urb = edge_port->port->read_urb;
		status = usb_submit_urb(urb, GFP_ATOMIC);
	}
	edge_port->ep_read_urb_state = EDGE_READ_URB_RUNNING;
	edge_port->shadow_mcr |= MCR_RTS;

	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	return status;
}