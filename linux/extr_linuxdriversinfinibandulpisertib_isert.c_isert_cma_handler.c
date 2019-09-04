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
struct rdma_cm_id {TYPE_1__* qp; struct isert_np* context; } ;
struct rdma_cm_event {int event; int /*<<< orphan*/  status; } ;
struct isert_np {struct rdma_cm_id* cm_id; } ;
struct isert_conn {int dev_removed; int /*<<< orphan*/  state; int /*<<< orphan*/  rem_wait; } ;
struct TYPE_2__ {struct isert_conn* qp_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_CONN_DOWN ; 
#define  RDMA_CM_EVENT_ADDR_CHANGE 136 
#define  RDMA_CM_EVENT_CONNECT_ERROR 135 
#define  RDMA_CM_EVENT_CONNECT_REQUEST 134 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 133 
#define  RDMA_CM_EVENT_DISCONNECTED 132 
#define  RDMA_CM_EVENT_ESTABLISHED 131 
#define  RDMA_CM_EVENT_REJECTED 130 
#define  RDMA_CM_EVENT_TIMEWAIT_EXIT 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 int isert_connect_error (struct rdma_cm_id*) ; 
 int isert_connect_request (struct rdma_cm_id*,struct rdma_cm_event*) ; 
 int /*<<< orphan*/  isert_connected_handler (struct rdma_cm_id*) ; 
 int isert_disconnected_handler (struct rdma_cm_id*,int) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int /*<<< orphan*/  isert_info (char*,int /*<<< orphan*/ ,...) ; 
 int isert_np_cma_handler (struct isert_np*,int) ; 
 int /*<<< orphan*/  kfree (struct isert_conn*) ; 
 int /*<<< orphan*/  rdma_event_msg (int) ; 
 int /*<<< orphan*/  rdma_reject_msg (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isert_cma_handler(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	struct isert_np *isert_np = cma_id->context;
	struct isert_conn *isert_conn;
	int ret = 0;

	isert_info("%s (%d): status %d id %p np %p\n",
		   rdma_event_msg(event->event), event->event,
		   event->status, cma_id, cma_id->context);

	if (isert_np->cm_id == cma_id)
		return isert_np_cma_handler(cma_id->context, event->event);

	switch (event->event) {
	case RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = isert_connect_request(cma_id, event);
		if (ret)
			isert_err("failed handle connect request %d\n", ret);
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		isert_connected_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ADDR_CHANGE:    /* FALLTHRU */
	case RDMA_CM_EVENT_DISCONNECTED:   /* FALLTHRU */
	case RDMA_CM_EVENT_TIMEWAIT_EXIT:  /* FALLTHRU */
		ret = isert_disconnected_handler(cma_id, event->event);
		break;
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
		isert_conn = cma_id->qp->qp_context;
		isert_conn->dev_removed = true;
		isert_disconnected_handler(cma_id, event->event);
		wait_event_interruptible(isert_conn->rem_wait,
					 isert_conn->state == ISER_CONN_DOWN);
		kfree(isert_conn);
		/*
		 * return non-zero from the callback to destroy
		 * the rdma cm id
		 */
		return 1;
	case RDMA_CM_EVENT_REJECTED:
		isert_info("Connection rejected: %s\n",
			   rdma_reject_msg(cma_id, event->status));
		/* fall through */
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_CONNECT_ERROR:
		ret = isert_connect_error(cma_id);
		break;
	default:
		isert_err("Unhandled RDMA CMA event: %d\n", event->event);
		break;
	}

	return ret;
}