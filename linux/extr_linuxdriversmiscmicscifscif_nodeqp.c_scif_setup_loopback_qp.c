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
struct scif_qp {int /*<<< orphan*/  local_write; int /*<<< orphan*/  local_read; int /*<<< orphan*/  inbound_q; int /*<<< orphan*/  outbound_q; int /*<<< orphan*/  recv_lock; int /*<<< orphan*/  send_lock; int /*<<< orphan*/  magic; } ;
struct scif_dev {int node; struct scif_qp* qpairs; } ;
struct TYPE_2__ {int nodeid; int /*<<< orphan*/  loopb_wq; struct scif_dev* loopb_dev; int /*<<< orphan*/  loopb_work; int /*<<< orphan*/  loopb_wqname; int /*<<< orphan*/  loopb_recv_q; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIFEP_MAGIC ; 
 int SCIF_NODE_QP_SIZE ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 
 int /*<<< orphan*/  kfree (struct scif_qp*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_destroy_intr_wq (struct scif_dev*) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  scif_loopb_wq_handler ; 
 int /*<<< orphan*/  scif_peer_register_device (struct scif_dev*) ; 
 int /*<<< orphan*/  scif_rb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int scif_setup_intr_wq (struct scif_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int scif_setup_loopback_qp(struct scif_dev *scifdev)
{
	int err = 0;
	void *local_q;
	struct scif_qp *qp;

	err = scif_setup_intr_wq(scifdev);
	if (err)
		goto exit;
	INIT_LIST_HEAD(&scif_info.loopb_recv_q);
	snprintf(scif_info.loopb_wqname, sizeof(scif_info.loopb_wqname),
		 "SCIF LOOPB %d", scifdev->node);
	scif_info.loopb_wq =
		alloc_ordered_workqueue(scif_info.loopb_wqname, 0);
	if (!scif_info.loopb_wq) {
		err = -ENOMEM;
		goto destroy_intr;
	}
	INIT_WORK(&scif_info.loopb_work, scif_loopb_wq_handler);
	/* Allocate Self Qpair */
	scifdev->qpairs = kzalloc(sizeof(*scifdev->qpairs), GFP_KERNEL);
	if (!scifdev->qpairs) {
		err = -ENOMEM;
		goto destroy_loopb_wq;
	}

	qp = scifdev->qpairs;
	qp->magic = SCIFEP_MAGIC;
	spin_lock_init(&qp->send_lock);
	spin_lock_init(&qp->recv_lock);

	local_q = kzalloc(SCIF_NODE_QP_SIZE, GFP_KERNEL);
	if (!local_q) {
		err = -ENOMEM;
		goto free_qpairs;
	}
	/*
	 * For loopback the inbound_q and outbound_q are essentially the same
	 * since the Node sends a message on the loopback interface to the
	 * outbound_q which is then received on the inbound_q.
	 */
	scif_rb_init(&qp->outbound_q,
		     &qp->local_read,
		     &qp->local_write,
		     local_q, get_count_order(SCIF_NODE_QP_SIZE));

	scif_rb_init(&qp->inbound_q,
		     &qp->local_read,
		     &qp->local_write,
		     local_q, get_count_order(SCIF_NODE_QP_SIZE));
	scif_info.nodeid = scifdev->node;

	scif_peer_register_device(scifdev);

	scif_info.loopb_dev = scifdev;
	return err;
free_qpairs:
	kfree(scifdev->qpairs);
destroy_loopb_wq:
	destroy_workqueue(scif_info.loopb_wq);
destroy_intr:
	scif_destroy_intr_wq(scifdev);
exit:
	return err;
}