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
struct TYPE_2__ {int size; struct scif_qp* rb_base; } ;
struct scif_qp {int /*<<< orphan*/  local_qp; TYPE_1__ inbound_q; int /*<<< orphan*/  local_buf; } ;
struct scif_dev {struct scif_qp* qpairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scif_qp*) ; 
 int /*<<< orphan*/  scif_unmap_single (int /*<<< orphan*/ ,struct scif_dev*,int) ; 

void scif_free_qp(struct scif_dev *scifdev)
{
	struct scif_qp *qp = scifdev->qpairs;

	if (!qp)
		return;
	scif_unmap_single(qp->local_buf, scifdev, qp->inbound_q.size);
	kfree(qp->inbound_q.rb_base);
	scif_unmap_single(qp->local_qp, scifdev, sizeof(struct scif_qp));
	kfree(scifdev->qpairs);
	scifdev->qpairs = NULL;
}