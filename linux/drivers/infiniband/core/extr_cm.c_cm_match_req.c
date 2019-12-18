#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_cm_id {int /*<<< orphan*/  state; int /*<<< orphan*/  device; } ;
struct cm_work {TYPE_3__* mad_recv_wc; int /*<<< orphan*/  port; } ;
struct TYPE_6__ {int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct cm_timewait_info {TYPE_2__ work; } ;
struct cm_req_msg {int /*<<< orphan*/  service_id; } ;
struct cm_id_private {int /*<<< orphan*/  work_count; struct ib_cm_id id; int /*<<< orphan*/  refcount; int /*<<< orphan*/  timewait_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {scalar_t__ mad; } ;
struct TYPE_7__ {TYPE_1__ recv_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_MSG_RESPONSE_REQ ; 
 int /*<<< orphan*/  IB_CM_REJ_INVALID_SERVICE_ID ; 
 int /*<<< orphan*/  IB_CM_REJ_STALE_CONN ; 
 int /*<<< orphan*/  IB_CM_REQ_RCVD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_4__ cm ; 
 int /*<<< orphan*/  cm_cleanup_timewait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_dup_req_handler (struct cm_work*,struct cm_id_private*) ; 
 struct cm_id_private* cm_find_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cm_id_private* cm_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cm_timewait_info* cm_insert_remote_id (int /*<<< orphan*/ ) ; 
 struct cm_timewait_info* cm_insert_remote_qpn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_issue_rej (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_send_cm_dreq (struct ib_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cm_id_private * cm_match_req(struct cm_work *work,
					   struct cm_id_private *cm_id_priv)
{
	struct cm_id_private *listen_cm_id_priv, *cur_cm_id_priv;
	struct cm_timewait_info *timewait_info;
	struct cm_req_msg *req_msg;
	struct ib_cm_id *cm_id;

	req_msg = (struct cm_req_msg *)work->mad_recv_wc->recv_buf.mad;

	/* Check for possible duplicate REQ. */
	spin_lock_irq(&cm.lock);
	timewait_info = cm_insert_remote_id(cm_id_priv->timewait_info);
	if (timewait_info) {
		cur_cm_id_priv = cm_get_id(timewait_info->work.local_id,
					   timewait_info->work.remote_id);
		spin_unlock_irq(&cm.lock);
		if (cur_cm_id_priv) {
			cm_dup_req_handler(work, cur_cm_id_priv);
			cm_deref_id(cur_cm_id_priv);
		}
		return NULL;
	}

	/* Check for stale connections. */
	timewait_info = cm_insert_remote_qpn(cm_id_priv->timewait_info);
	if (timewait_info) {
		cm_cleanup_timewait(cm_id_priv->timewait_info);
		cur_cm_id_priv = cm_get_id(timewait_info->work.local_id,
					   timewait_info->work.remote_id);

		spin_unlock_irq(&cm.lock);
		cm_issue_rej(work->port, work->mad_recv_wc,
			     IB_CM_REJ_STALE_CONN, CM_MSG_RESPONSE_REQ,
			     NULL, 0);
		if (cur_cm_id_priv) {
			cm_id = &cur_cm_id_priv->id;
			ib_send_cm_dreq(cm_id, NULL, 0);
			cm_deref_id(cur_cm_id_priv);
		}
		return NULL;
	}

	/* Find matching listen request. */
	listen_cm_id_priv = cm_find_listen(cm_id_priv->id.device,
					   req_msg->service_id);
	if (!listen_cm_id_priv) {
		cm_cleanup_timewait(cm_id_priv->timewait_info);
		spin_unlock_irq(&cm.lock);
		cm_issue_rej(work->port, work->mad_recv_wc,
			     IB_CM_REJ_INVALID_SERVICE_ID, CM_MSG_RESPONSE_REQ,
			     NULL, 0);
		goto out;
	}
	atomic_inc(&listen_cm_id_priv->refcount);
	atomic_inc(&cm_id_priv->refcount);
	cm_id_priv->id.state = IB_CM_REQ_RCVD;
	atomic_inc(&cm_id_priv->work_count);
	spin_unlock_irq(&cm.lock);
out:
	return listen_cm_id_priv;
}