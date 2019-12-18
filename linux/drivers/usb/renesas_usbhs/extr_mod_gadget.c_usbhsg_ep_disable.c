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
struct usbhsg_uep {int /*<<< orphan*/  lock; TYPE_1__* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct usb_ep {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mod_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbhs_pipe_free (struct usbhs_pipe*) ; 
 struct usbhsg_uep* usbhsg_ep_to_uep (struct usb_ep*) ; 
 int /*<<< orphan*/  usbhsg_pipe_disable (struct usbhsg_uep*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 

__attribute__((used)) static int usbhsg_ep_disable(struct usb_ep *ep)
{
	struct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	struct usbhs_pipe *pipe;
	unsigned long flags;

	spin_lock_irqsave(&uep->lock, flags);
	pipe = usbhsg_uep_to_pipe(uep);
	if (!pipe)
		goto out;

	usbhsg_pipe_disable(uep);
	usbhs_pipe_free(pipe);

	uep->pipe->mod_private	= NULL;
	uep->pipe		= NULL;

out:
	spin_unlock_irqrestore(&uep->lock, flags);

	return 0;
}