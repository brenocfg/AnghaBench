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
struct TYPE_4__ {int size; int /*<<< orphan*/ * rb_base; } ;
struct scif_qp {int local_qp; int local_buf; int /*<<< orphan*/ * remote_qp; TYPE_2__ outbound_q; } ;
struct TYPE_3__ {struct scif_qp* qp; } ;
struct scif_endpt {int /*<<< orphan*/  remote_dev; TYPE_1__ qp_info; } ;

/* Variables and functions */
 int SCIF_ENDPT_QP_SIZE ; 
 int /*<<< orphan*/  scif_iounmap (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_unmap_single (int,int /*<<< orphan*/ ,int) ; 

void scif_cleanup_ep_qp(struct scif_endpt *ep)
{
	struct scif_qp *qp = ep->qp_info.qp;

	if (qp->outbound_q.rb_base) {
		scif_iounmap((void *)qp->outbound_q.rb_base,
			     qp->outbound_q.size, ep->remote_dev);
		qp->outbound_q.rb_base = NULL;
	}
	if (qp->remote_qp) {
		scif_iounmap((void *)qp->remote_qp,
			     sizeof(struct scif_qp), ep->remote_dev);
		qp->remote_qp = NULL;
	}
	if (qp->local_qp) {
		scif_unmap_single(qp->local_qp, ep->remote_dev,
				  sizeof(struct scif_qp));
		qp->local_qp = 0x0;
	}
	if (qp->local_buf) {
		scif_unmap_single(qp->local_buf, ep->remote_dev,
				  SCIF_ENDPT_QP_SIZE);
		qp->local_buf = 0;
	}
}