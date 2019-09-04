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
struct scif_qp {int /*<<< orphan*/  magic; } ;
struct scif_dev {struct scif_qp* qpairs; int /*<<< orphan*/  qp_dma_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCIFEP_MAGIC ; 
 int SCIF_NODE_QP_SIZE ; 
 int /*<<< orphan*/  kfree (struct scif_qp*) ; 
 struct scif_qp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int scif_setup_qp_connect (struct scif_qp*,int /*<<< orphan*/ *,int,struct scif_dev*) ; 

int scif_setup_qp(struct scif_dev *scifdev)
{
	int err = 0;
	int local_size;
	struct scif_qp *qp;

	local_size = SCIF_NODE_QP_SIZE;

	qp = kzalloc(sizeof(*qp), GFP_KERNEL);
	if (!qp) {
		err = -ENOMEM;
		return err;
	}
	qp->magic = SCIFEP_MAGIC;
	scifdev->qpairs = qp;
	err = scif_setup_qp_connect(qp, &scifdev->qp_dma_addr,
				    local_size, scifdev);
	if (err)
		goto free_qp;
	/*
	 * We're as setup as we can be. The inbound_q is setup, w/o a usable
	 * outbound q.  When we get a message, the read_ptr will be updated,
	 * and we will pull the message.
	 */
	return err;
free_qp:
	kfree(scifdev->qpairs);
	scifdev->qpairs = NULL;
	return err;
}