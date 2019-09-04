#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ib_qp {TYPE_1__* qp_sec; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  security; int /*<<< orphan*/  error_complete; int /*<<< orphan*/  error_list_count; int /*<<< orphan*/  shared_qp_list; int /*<<< orphan*/  mutex; struct ib_device* dev; struct ib_qp* qp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_end_port (struct ib_device*) ; 
 int rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_start_port (struct ib_device*) ; 
 int security_ib_alloc_security (int /*<<< orphan*/ *) ; 

int ib_create_qp_security(struct ib_qp *qp, struct ib_device *dev)
{
	u8 i = rdma_start_port(dev);
	bool is_ib = false;
	int ret;

	while (i <= rdma_end_port(dev) && !is_ib)
		is_ib = rdma_protocol_ib(dev, i++);

	/* If this isn't an IB device don't create the security context */
	if (!is_ib)
		return 0;

	qp->qp_sec = kzalloc(sizeof(*qp->qp_sec), GFP_KERNEL);
	if (!qp->qp_sec)
		return -ENOMEM;

	qp->qp_sec->qp = qp;
	qp->qp_sec->dev = dev;
	mutex_init(&qp->qp_sec->mutex);
	INIT_LIST_HEAD(&qp->qp_sec->shared_qp_list);
	atomic_set(&qp->qp_sec->error_list_count, 0);
	init_completion(&qp->qp_sec->error_complete);
	ret = security_ib_alloc_security(&qp->qp_sec->security);
	if (ret) {
		kfree(qp->qp_sec);
		qp->qp_sec = NULL;
	}

	return ret;
}