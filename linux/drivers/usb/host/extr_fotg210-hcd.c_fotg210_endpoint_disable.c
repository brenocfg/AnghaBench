#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {struct fotg210_qh* hcpriv; TYPE_4__ desc; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_7__ {struct fotg210_qh* qh; } ;
struct fotg210_qh {int qh_state; int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  clearing_tt; TYPE_3__ qh_next; int /*<<< orphan*/  td_list; int /*<<< orphan*/ * hw; } ;
struct fotg210_iso_stream {int qh_state; int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  clearing_tt; TYPE_3__ qh_next; int /*<<< orphan*/  td_list; int /*<<< orphan*/ * hw; } ;
struct fotg210_hcd {scalar_t__ rh_state; int /*<<< orphan*/  lock; TYPE_2__* async; } ;
struct TYPE_5__ {struct fotg210_qh* qh; } ;
struct TYPE_6__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 scalar_t__ FOTG210_RH_RUNNING ; 
#define  QH_STATE_COMPLETING 132 
#define  QH_STATE_IDLE 131 
#define  QH_STATE_LINKED 130 
#define  QH_STATE_UNLINK 129 
#define  QH_STATE_UNLINK_WAIT 128 
 int /*<<< orphan*/  fotg210_err (struct fotg210_hcd*,char*,struct fotg210_qh*,int /*<<< orphan*/ ,int,char*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  kfree (struct fotg210_qh*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_destroy (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_unlink_async (struct fotg210_hcd*,struct fotg210_qh*) ; 

__attribute__((used)) static void fotg210_endpoint_disable(struct usb_hcd *hcd,
		struct usb_host_endpoint *ep)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	unsigned long flags;
	struct fotg210_qh *qh, *tmp;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs for this any more */

rescan:
	spin_lock_irqsave(&fotg210->lock, flags);
	qh = ep->hcpriv;
	if (!qh)
		goto done;

	/* endpoints can be iso streams.  for now, we don't
	 * accelerate iso completions ... so spin a while.
	 */
	if (qh->hw == NULL) {
		struct fotg210_iso_stream *stream = ep->hcpriv;

		if (!list_empty(&stream->td_list))
			goto idle_timeout;

		/* BUG_ON(!list_empty(&stream->free_list)); */
		kfree(stream);
		goto done;
	}

	if (fotg210->rh_state < FOTG210_RH_RUNNING)
		qh->qh_state = QH_STATE_IDLE;
	switch (qh->qh_state) {
	case QH_STATE_LINKED:
	case QH_STATE_COMPLETING:
		for (tmp = fotg210->async->qh_next.qh;
				tmp && tmp != qh;
				tmp = tmp->qh_next.qh)
			continue;
		/* periodic qh self-unlinks on empty, and a COMPLETING qh
		 * may already be unlinked.
		 */
		if (tmp)
			start_unlink_async(fotg210, qh);
		/* FALL THROUGH */
	case QH_STATE_UNLINK:		/* wait for hw to finish? */
	case QH_STATE_UNLINK_WAIT:
idle_timeout:
		spin_unlock_irqrestore(&fotg210->lock, flags);
		schedule_timeout_uninterruptible(1);
		goto rescan;
	case QH_STATE_IDLE:		/* fully unlinked */
		if (qh->clearing_tt)
			goto idle_timeout;
		if (list_empty(&qh->qtd_list)) {
			qh_destroy(fotg210, qh);
			break;
		}
		/* fall through */
	default:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  just leak this memory.
		 */
		fotg210_err(fotg210, "qh %p (#%02x) state %d%s\n",
				qh, ep->desc.bEndpointAddress, qh->qh_state,
				list_empty(&qh->qtd_list) ? "" : "(has tds)");
		break;
	}
done:
	ep->hcpriv = NULL;
	spin_unlock_irqrestore(&fotg210->lock, flags);
}