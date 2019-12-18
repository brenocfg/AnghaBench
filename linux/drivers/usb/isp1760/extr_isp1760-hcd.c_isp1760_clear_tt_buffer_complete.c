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
struct usb_host_endpoint {struct isp1760_qh* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct isp1760_qh {scalar_t__ tt_buffer_dirty; } ;
struct isp1760_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  schedule_ptds (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void isp1760_clear_tt_buffer_complete(struct usb_hcd *hcd,
						struct usb_host_endpoint *ep)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	struct isp1760_qh *qh = ep->hcpriv;
	unsigned long spinflags;

	if (!qh)
		return;

	spin_lock_irqsave(&priv->lock, spinflags);
	qh->tt_buffer_dirty = 0;
	schedule_ptds(hcd);
	spin_unlock_irqrestore(&priv->lock, spinflags);
}