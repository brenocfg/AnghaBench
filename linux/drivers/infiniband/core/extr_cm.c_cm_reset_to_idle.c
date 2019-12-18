#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct cm_id_private {int /*<<< orphan*/ * timewait_info; TYPE_1__ id; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CM_IDLE ; 
 TYPE_2__ cm ; 
 int /*<<< orphan*/  cm_cleanup_timewait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cm_reset_to_idle(struct cm_id_private *cm_id_priv)
{
	unsigned long flags;

	cm_id_priv->id.state = IB_CM_IDLE;
	if (cm_id_priv->timewait_info) {
		spin_lock_irqsave(&cm.lock, flags);
		cm_cleanup_timewait(cm_id_priv->timewait_info);
		spin_unlock_irqrestore(&cm.lock, flags);
		kfree(cm_id_priv->timewait_info);
		cm_id_priv->timewait_info = NULL;
	}
}