#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rdma_cm_id {scalar_t__ context; } ;
struct TYPE_4__ {int /*<<< orphan*/  private_data; } ;
struct TYPE_5__ {TYPE_1__ conn; } ;
struct rdma_cm_event {int event; int /*<<< orphan*/  status; TYPE_2__ param; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cma_id; } ;
struct iser_conn {int /*<<< orphan*/  state_mutex; TYPE_3__ ib_conn; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_CONN_DOWN ; 
#define  RDMA_CM_EVENT_ADDR_CHANGE 139 
#define  RDMA_CM_EVENT_ADDR_ERROR 138 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 137 
#define  RDMA_CM_EVENT_CONNECT_ERROR 136 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 135 
#define  RDMA_CM_EVENT_DISCONNECTED 134 
#define  RDMA_CM_EVENT_ESTABLISHED 133 
#define  RDMA_CM_EVENT_REJECTED 132 
#define  RDMA_CM_EVENT_ROUTE_ERROR 131 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 130 
#define  RDMA_CM_EVENT_TIMEWAIT_EXIT 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 int /*<<< orphan*/  iser_addr_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_cleanup_handler (struct rdma_cm_id*,int) ; 
 int /*<<< orphan*/  iser_connect_error (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_connected_handler (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iser_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  iser_route_handler (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_event_msg (int) ; 
 int /*<<< orphan*/  rdma_reject_msg (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iser_cma_handler(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	struct iser_conn *iser_conn;
	int ret = 0;

	iser_conn = (struct iser_conn *)cma_id->context;
	iser_info("%s (%d): status %d conn %p id %p\n",
		  rdma_event_msg(event->event), event->event,
		  event->status, cma_id->context, cma_id);

	mutex_lock(&iser_conn->state_mutex);
	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		iser_addr_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		iser_route_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		iser_connected_handler(cma_id, event->param.conn.private_data);
		break;
	case RDMA_CM_EVENT_REJECTED:
		iser_info("Connection rejected: %s\n",
			 rdma_reject_msg(cma_id, event->status));
		/* FALLTHROUGH */
	case RDMA_CM_EVENT_ADDR_ERROR:
	case RDMA_CM_EVENT_ROUTE_ERROR:
	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
		iser_connect_error(cma_id);
		break;
	case RDMA_CM_EVENT_DISCONNECTED:
	case RDMA_CM_EVENT_ADDR_CHANGE:
	case RDMA_CM_EVENT_TIMEWAIT_EXIT:
		iser_cleanup_handler(cma_id, false);
		break;
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
		/*
		 * we *must* destroy the device as we cannot rely
		 * on iscsid to be around to initiate error handling.
		 * also if we are not in state DOWN implicitly destroy
		 * the cma_id.
		 */
		iser_cleanup_handler(cma_id, true);
		if (iser_conn->state != ISER_CONN_DOWN) {
			iser_conn->ib_conn.cma_id = NULL;
			ret = 1;
		}
		break;
	default:
		iser_err("Unexpected RDMA CM event: %s (%d)\n",
			 rdma_event_msg(event->event), event->event);
		break;
	}
	mutex_unlock(&iser_conn->state_mutex);

	return ret;
}