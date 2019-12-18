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
struct renesas_usb3_ep {int dummy; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __usb3_request_done (struct renesas_usb3_ep*,struct renesas_usb3_request*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 

__attribute__((used)) static void usb3_request_done(struct renesas_usb3_ep *usb3_ep,
			      struct renesas_usb3_request *usb3_req, int status)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	unsigned long flags;

	spin_lock_irqsave(&usb3->lock, flags);
	__usb3_request_done(usb3_ep, usb3_req, status);
	spin_unlock_irqrestore(&usb3->lock, flags);
}