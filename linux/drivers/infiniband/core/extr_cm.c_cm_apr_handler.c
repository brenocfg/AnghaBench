#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  info_len; int /*<<< orphan*/ * apr_info; int /*<<< orphan*/  ap_status; } ;
struct TYPE_17__ {TYPE_5__ apr_rcvd; } ;
struct TYPE_18__ {int /*<<< orphan*/ * private_data; TYPE_6__ param; } ;
struct cm_work {int /*<<< orphan*/  list; TYPE_7__ cm_event; TYPE_4__* mad_recv_wc; TYPE_2__* port; } ;
struct TYPE_11__ {TYPE_9__* port; } ;
struct TYPE_19__ {scalar_t__ state; scalar_t__ lap_state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; int /*<<< orphan*/ * msg; TYPE_10__ av; TYPE_8__ id; } ;
struct cm_apr_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  info_length; int /*<<< orphan*/  info; int /*<<< orphan*/  ap_status; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  remote_comm_id; } ;
struct TYPE_20__ {int /*<<< orphan*/  mad_agent; } ;
struct TYPE_14__ {scalar_t__ mad; } ;
struct TYPE_15__ {TYPE_3__ recv_buf; } ;
struct TYPE_13__ {int /*<<< orphan*/  port_num; TYPE_1__* cm_dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_CM_ESTABLISHED ; 
 scalar_t__ IB_CM_LAP_IDLE ; 
 scalar_t__ IB_CM_LAP_SENT ; 
 scalar_t__ IB_CM_MRA_LAP_RCVD ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 struct cm_id_private* cm_acquire_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  ib_cancel_mad (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_protocol_roce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_apr_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	struct cm_apr_msg *apr_msg;
	int ret;

	/* Currently Alternate path messages are not supported for
	 * RoCE link layer.
	 */
	if (rdma_protocol_roce(work->port->cm_dev->ib_device,
			       work->port->port_num))
		return -EINVAL;

	apr_msg = (struct cm_apr_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(apr_msg->remote_comm_id,
				   apr_msg->local_comm_id);
	if (!cm_id_priv)
		return -EINVAL; /* Unmatched reply. */

	work->cm_event.param.apr_rcvd.ap_status = apr_msg->ap_status;
	work->cm_event.param.apr_rcvd.apr_info = &apr_msg->info;
	work->cm_event.param.apr_rcvd.info_len = apr_msg->info_length;
	work->cm_event.private_data = &apr_msg->private_data;

	spin_lock_irq(&cm_id_priv->lock);
	if (cm_id_priv->id.state != IB_CM_ESTABLISHED ||
	    (cm_id_priv->id.lap_state != IB_CM_LAP_SENT &&
	     cm_id_priv->id.lap_state != IB_CM_MRA_LAP_RCVD)) {
		spin_unlock_irq(&cm_id_priv->lock);
		goto out;
	}
	cm_id_priv->id.lap_state = IB_CM_LAP_IDLE;
	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	cm_id_priv->msg = NULL;

	ret = atomic_inc_and_test(&cm_id_priv->work_count);
	if (!ret)
		list_add_tail(&work->list, &cm_id_priv->work_list);
	spin_unlock_irq(&cm_id_priv->lock);

	if (ret)
		cm_process_work(cm_id_priv, work);
	else
		cm_deref_id(cm_id_priv);
	return 0;
out:
	cm_deref_id(cm_id_priv);
	return -EINVAL;
}