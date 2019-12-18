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
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {int /*<<< orphan*/  num; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb3_disable_pipe_irq (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 struct renesas_usb3_request* usb3_get_request (struct renesas_usb3_ep*) ; 
 scalar_t__ usb3_pn_change (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_pn_stop (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_request_done (struct renesas_usb3_ep*,struct renesas_usb3_request*,int) ; 
 int /*<<< orphan*/  usb3_start_pipen (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 

__attribute__((used)) static void usb3_request_done_pipen(struct renesas_usb3 *usb3,
				    struct renesas_usb3_ep *usb3_ep,
				    struct renesas_usb3_request *usb3_req,
				    int status)
{
	unsigned long flags;

	spin_lock_irqsave(&usb3->lock, flags);
	if (usb3_pn_change(usb3, usb3_ep->num))
		usb3_pn_stop(usb3);
	spin_unlock_irqrestore(&usb3->lock, flags);

	usb3_disable_pipe_irq(usb3, usb3_ep->num);
	usb3_request_done(usb3_ep, usb3_req, status);

	/* get next usb3_req */
	usb3_req = usb3_get_request(usb3_ep);
	if (usb3_req)
		usb3_start_pipen(usb3_ep, usb3_req);
}