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
struct TYPE_6__ {int (* cm_handler ) (TYPE_3__*,struct iw_cm_event*) ;TYPE_2__* device; } ;
struct iwcm_id_private {int state; TYPE_3__ id; int /*<<< orphan*/  lock; struct ib_qp* qp; } ;
struct iw_cm_event {int dummy; } ;
struct ib_qp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* iw_rem_ref ) (struct ib_qp*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  IW_CM_STATE_CLOSING 130 
#define  IW_CM_STATE_DESTROYING 129 
#define  IW_CM_STATE_ESTABLISHED 128 
 int IW_CM_STATE_IDLE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ib_qp*) ; 
 int stub2 (TYPE_3__*,struct iw_cm_event*) ; 

__attribute__((used)) static int cm_close_handler(struct iwcm_id_private *cm_id_priv,
				  struct iw_cm_event *iw_event)
{
	struct ib_qp *qp;
	unsigned long flags;
	int ret = 0, notify_event = 0;
	spin_lock_irqsave(&cm_id_priv->lock, flags);
	qp = cm_id_priv->qp;
	cm_id_priv->qp = NULL;

	switch (cm_id_priv->state) {
	case IW_CM_STATE_ESTABLISHED:
	case IW_CM_STATE_CLOSING:
		cm_id_priv->state = IW_CM_STATE_IDLE;
		notify_event = 1;
		break;
	case IW_CM_STATE_DESTROYING:
		break;
	default:
		BUG();
	}
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);

	if (qp)
		cm_id_priv->id.device->ops.iw_rem_ref(qp);
	if (notify_event)
		ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, iw_event);
	return ret;
}