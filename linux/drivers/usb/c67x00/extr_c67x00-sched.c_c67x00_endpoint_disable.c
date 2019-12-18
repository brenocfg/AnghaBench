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
struct usb_host_endpoint {int /*<<< orphan*/  urb_list; } ;
struct usb_hcd {int dummy; } ;
struct c67x00_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  endpoint_disable; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ c67x00_ep_data_free (struct usb_host_endpoint*) ; 
 int /*<<< orphan*/  c67x00_hcd_dev (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  c67x00_sched_kick (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct c67x00_hcd* hcd_to_c67x00_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

void c67x00_endpoint_disable(struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	struct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	unsigned long flags;

	if (!list_empty(&ep->urb_list))
		dev_warn(c67x00_hcd_dev(c67x00), "error: urb list not empty\n");

	spin_lock_irqsave(&c67x00->lock, flags);

	/* loop waiting for all transfers in the endpoint queue to complete */
	while (c67x00_ep_data_free(ep)) {
		/* Drop the lock so we can sleep waiting for the hardware */
		spin_unlock_irqrestore(&c67x00->lock, flags);

		/* it could happen that we reinitialize this completion, while
		 * somebody was waiting for that completion.  The timeout and
		 * while loop handle such cases, but this might be improved */
		reinit_completion(&c67x00->endpoint_disable);
		c67x00_sched_kick(c67x00);
		wait_for_completion_timeout(&c67x00->endpoint_disable, 1 * HZ);

		spin_lock_irqsave(&c67x00->lock, flags);
	}

	spin_unlock_irqrestore(&c67x00->lock, flags);
}