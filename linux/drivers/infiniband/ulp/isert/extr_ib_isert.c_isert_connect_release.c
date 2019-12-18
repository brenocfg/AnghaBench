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
struct isert_device {int dummy; } ;
struct isert_conn {int /*<<< orphan*/  rem_wait; scalar_t__ dev_removed; scalar_t__ login_req_buf; TYPE_2__* qp; scalar_t__ cm_id; struct isert_device* device; } ;
struct isert_comp {int dummy; } ;
struct TYPE_4__ {TYPE_1__* recv_cq; } ;
struct TYPE_3__ {struct isert_comp* cq_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ib_destroy_qp (TYPE_2__*) ; 
 int /*<<< orphan*/  isert_comp_put (struct isert_comp*) ; 
 int /*<<< orphan*/  isert_dbg (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_device_put (struct isert_device*) ; 
 int /*<<< orphan*/  isert_free_login_buf (struct isert_conn*) ; 
 int /*<<< orphan*/  isert_free_rx_descriptors (struct isert_conn*) ; 
 int /*<<< orphan*/  kfree (struct isert_conn*) ; 
 int /*<<< orphan*/  rdma_destroy_id (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_connect_release(struct isert_conn *isert_conn)
{
	struct isert_device *device = isert_conn->device;

	isert_dbg("conn %p\n", isert_conn);

	BUG_ON(!device);

	isert_free_rx_descriptors(isert_conn);
	if (isert_conn->cm_id &&
	    !isert_conn->dev_removed)
		rdma_destroy_id(isert_conn->cm_id);

	if (isert_conn->qp) {
		struct isert_comp *comp = isert_conn->qp->recv_cq->cq_context;

		isert_comp_put(comp);
		ib_destroy_qp(isert_conn->qp);
	}

	if (isert_conn->login_req_buf)
		isert_free_login_buf(isert_conn);

	isert_device_put(device);

	if (isert_conn->dev_removed)
		wake_up_interruptible(&isert_conn->rem_wait);
	else
		kfree(isert_conn);
}