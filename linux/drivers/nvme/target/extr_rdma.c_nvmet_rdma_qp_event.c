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
struct nvmet_rdma_queue {int /*<<< orphan*/  cm_id; } ;
struct ib_event {int event; } ;

/* Variables and functions */
#define  IB_EVENT_COMM_EST 128 
 int /*<<< orphan*/  ib_event_msg (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_notify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nvmet_rdma_qp_event(struct ib_event *event, void *priv)
{
	struct nvmet_rdma_queue *queue = priv;

	switch (event->event) {
	case IB_EVENT_COMM_EST:
		rdma_notify(queue->cm_id, event->event);
		break;
	default:
		pr_err("received IB QP event: %s (%d)\n",
		       ib_event_msg(event->event), event->event);
		break;
	}
}