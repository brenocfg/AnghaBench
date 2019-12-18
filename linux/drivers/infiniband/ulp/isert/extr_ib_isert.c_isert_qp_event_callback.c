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
struct isert_conn {int /*<<< orphan*/  cm_id; } ;
struct ib_event {int event; } ;

/* Variables and functions */
#define  IB_EVENT_COMM_EST 129 
#define  IB_EVENT_QP_LAST_WQE_REACHED 128 
 int /*<<< orphan*/  ib_event_msg (int) ; 
 int /*<<< orphan*/  isert_err (char*,int /*<<< orphan*/ ,int,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_warn (char*) ; 
 int /*<<< orphan*/  rdma_notify (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void
isert_qp_event_callback(struct ib_event *e, void *context)
{
	struct isert_conn *isert_conn = context;

	isert_err("%s (%d): conn %p\n",
		  ib_event_msg(e->event), e->event, isert_conn);

	switch (e->event) {
	case IB_EVENT_COMM_EST:
		rdma_notify(isert_conn->cm_id, IB_EVENT_COMM_EST);
		break;
	case IB_EVENT_QP_LAST_WQE_REACHED:
		isert_warn("Reached TX IB_EVENT_QP_LAST_WQE_REACHED\n");
		break;
	default:
		break;
	}
}