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
struct iwcm_id_private {int state; int /*<<< orphan*/  lock; } ;
struct ib_qp_attr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IW_CM_STATE_CONN_RECV 131 
#define  IW_CM_STATE_CONN_SENT 130 
#define  IW_CM_STATE_ESTABLISHED 129 
#define  IW_CM_STATE_IDLE 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iwcm_init_qp_rts_attr(struct iwcm_id_private *cm_id_priv,
				  struct ib_qp_attr *qp_attr,
				  int *qp_attr_mask)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	switch (cm_id_priv->state) {
	case IW_CM_STATE_IDLE:
	case IW_CM_STATE_CONN_SENT:
	case IW_CM_STATE_CONN_RECV:
	case IW_CM_STATE_ESTABLISHED:
		*qp_attr_mask = 0;
		ret = 0;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	return ret;
}