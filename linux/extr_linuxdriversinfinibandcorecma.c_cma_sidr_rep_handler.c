#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  path_rec; } ;
struct TYPE_13__ {int (* event_handler ) (TYPE_6__*,struct rdma_cm_event*) ;TYPE_2__ route; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ib; } ;
struct rdma_id_private {scalar_t__ state; int /*<<< orphan*/  handler_mutex; TYPE_6__ id; TYPE_5__ cm_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; } ;
struct TYPE_11__ {TYPE_3__ ud; } ;
struct rdma_cm_event {int status; TYPE_4__ param; void* event; } ;
struct ib_cm_sidr_rep_event_param {int status; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qpn; int /*<<< orphan*/  sgid_attr; } ;
struct ib_cm_id {struct rdma_id_private* context; } ;
struct TYPE_8__ {struct ib_cm_sidr_rep_event_param sidr_rep_rcvd; } ;
struct ib_cm_event {int event; TYPE_1__ param; int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IB_CM_SIDR_REP_PRIVATE_DATA_SIZE ; 
#define  IB_CM_SIDR_REP_RECEIVED 129 
#define  IB_CM_SIDR_REQ_ERROR 128 
 int IB_SIDR_SUCCESS ; 
 scalar_t__ RDMA_CM_CONNECT ; 
 int /*<<< orphan*/  RDMA_CM_DESTROYING ; 
 void* RDMA_CM_EVENT_ADDR_ERROR ; 
 void* RDMA_CM_EVENT_ESTABLISHED ; 
 void* RDMA_CM_EVENT_UNREACHABLE ; 
 int /*<<< orphan*/  cma_exch (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int cma_set_qkey (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_init_ah_attr_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rdma_destroy_ah_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_6__*) ; 
 int stub1 (TYPE_6__*,struct rdma_cm_event*) ; 

__attribute__((used)) static int cma_sidr_rep_handler(struct ib_cm_id *cm_id,
				const struct ib_cm_event *ib_event)
{
	struct rdma_id_private *id_priv = cm_id->context;
	struct rdma_cm_event event = {};
	const struct ib_cm_sidr_rep_event_param *rep =
				&ib_event->param.sidr_rep_rcvd;
	int ret = 0;

	mutex_lock(&id_priv->handler_mutex);
	if (id_priv->state != RDMA_CM_CONNECT)
		goto out;

	switch (ib_event->event) {
	case IB_CM_SIDR_REQ_ERROR:
		event.event = RDMA_CM_EVENT_UNREACHABLE;
		event.status = -ETIMEDOUT;
		break;
	case IB_CM_SIDR_REP_RECEIVED:
		event.param.ud.private_data = ib_event->private_data;
		event.param.ud.private_data_len = IB_CM_SIDR_REP_PRIVATE_DATA_SIZE;
		if (rep->status != IB_SIDR_SUCCESS) {
			event.event = RDMA_CM_EVENT_UNREACHABLE;
			event.status = ib_event->param.sidr_rep_rcvd.status;
			pr_debug_ratelimited("RDMA CM: UNREACHABLE: bad SIDR reply. status %d\n",
					     event.status);
			break;
		}
		ret = cma_set_qkey(id_priv, rep->qkey);
		if (ret) {
			pr_debug_ratelimited("RDMA CM: ADDR_ERROR: failed to set qkey. status %d\n", ret);
			event.event = RDMA_CM_EVENT_ADDR_ERROR;
			event.status = ret;
			break;
		}
		ib_init_ah_attr_from_path(id_priv->id.device,
					  id_priv->id.port_num,
					  id_priv->id.route.path_rec,
					  &event.param.ud.ah_attr,
					  rep->sgid_attr);
		event.param.ud.qp_num = rep->qpn;
		event.param.ud.qkey = rep->qkey;
		event.event = RDMA_CM_EVENT_ESTABLISHED;
		event.status = 0;
		break;
	default:
		pr_err("RDMA CMA: unexpected IB CM event: %d\n",
		       ib_event->event);
		goto out;
	}

	ret = id_priv->id.event_handler(&id_priv->id, &event);

	rdma_destroy_ah_attr(&event.param.ud.ah_attr);
	if (ret) {
		/* Destroy the CM ID by returning a non-zero value. */
		id_priv->cm_id.ib = NULL;
		cma_exch(id_priv, RDMA_CM_DESTROYING);
		mutex_unlock(&id_priv->handler_mutex);
		rdma_destroy_id(&id_priv->id);
		return ret;
	}
out:
	mutex_unlock(&id_priv->handler_mutex);
	return ret;
}