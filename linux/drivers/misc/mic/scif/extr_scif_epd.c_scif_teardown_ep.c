#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct scif_qp* rb_base; } ;
struct scif_qp {TYPE_2__ inbound_q; } ;
struct TYPE_3__ {struct scif_qp* qp; } ;
struct scif_endpt {int /*<<< orphan*/  lock; TYPE_1__ qp_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scif_qp*) ; 
 int /*<<< orphan*/  scif_cleanup_ep_qp (struct scif_endpt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void scif_teardown_ep(void *endpt)
{
	struct scif_endpt *ep = endpt;
	struct scif_qp *qp = ep->qp_info.qp;

	if (qp) {
		spin_lock(&ep->lock);
		scif_cleanup_ep_qp(ep);
		spin_unlock(&ep->lock);
		kfree(qp->inbound_q.rb_base);
		kfree(qp);
	}
}