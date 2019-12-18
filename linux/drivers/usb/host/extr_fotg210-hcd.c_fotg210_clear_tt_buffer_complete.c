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
struct usb_host_endpoint {struct fotg210_qh* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct fotg210_qh {scalar_t__ qh_state; int /*<<< orphan*/  qtd_list; scalar_t__ clearing_tt; } ;
struct fotg210_hcd {scalar_t__ rh_state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ FOTG210_RH_RUNNING ; 
 scalar_t__ QH_STATE_IDLE ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_link_async (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fotg210_clear_tt_buffer_complete(struct usb_hcd *hcd,
		struct usb_host_endpoint *ep)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	struct fotg210_qh *qh = ep->hcpriv;
	unsigned long flags;

	spin_lock_irqsave(&fotg210->lock, flags);
	qh->clearing_tt = 0;
	if (qh->qh_state == QH_STATE_IDLE && !list_empty(&qh->qtd_list)
			&& fotg210->rh_state == FOTG210_RH_RUNNING)
		qh_link_async(fotg210, qh);
	spin_unlock_irqrestore(&fotg210->lock, flags);
}