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
struct TYPE_4__ {scalar_t__ current_read_offset; scalar_t__ current_write_offset; } ;
struct TYPE_3__ {scalar_t__ rb_base; } ;
struct scif_qp {TYPE_2__ inbound_q; scalar_t__ local_write; int /*<<< orphan*/ * remote_qp; TYPE_1__ outbound_q; } ;
struct scif_dev {struct scif_qp* qpairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  scif_free_qp (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_iounmap (void*,int,struct scif_dev*) ; 
 scalar_t__ scifdev_is_p2p (struct scif_dev*) ; 

__attribute__((used)) static void scif_cleanup_qp(struct scif_dev *dev)
{
	struct scif_qp *qp = &dev->qpairs[0];

	if (!qp)
		return;
	scif_iounmap((void *)qp->remote_qp, sizeof(struct scif_qp), dev);
	scif_iounmap((void *)qp->outbound_q.rb_base,
		     sizeof(struct scif_qp), dev);
	qp->remote_qp = NULL;
	qp->local_write = 0;
	qp->inbound_q.current_write_offset = 0;
	qp->inbound_q.current_read_offset = 0;
	if (scifdev_is_p2p(dev))
		scif_free_qp(dev);
}