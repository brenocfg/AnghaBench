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
struct qede_rdma_event_work {int event; int /*<<< orphan*/  work; struct qede_dev* ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdma_wq; int /*<<< orphan*/  qedr_dev; scalar_t__ exp_recovery; } ;
struct qede_dev {TYPE_1__ rdma_info; } ;
typedef  enum qede_rdma_event { ____Placeholder_qede_rdma_event } qede_rdma_event ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qede_rdma_event_work* qede_rdma_get_free_event_node (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_rdma_handle_event ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qede_rdma_add_event(struct qede_dev *edev,
				enum qede_rdma_event event)
{
	struct qede_rdma_event_work *event_node;

	/* If a recovery was experienced avoid adding the event */
	if (edev->rdma_info.exp_recovery)
		return;

	if (!edev->rdma_info.qedr_dev)
		return;

	event_node = qede_rdma_get_free_event_node(edev);
	if (!event_node)
		return;

	event_node->event = event;
	event_node->ptr = edev;

	INIT_WORK(&event_node->work, qede_rdma_handle_event);
	queue_work(edev->rdma_info.rdma_wq, &event_node->work);
}