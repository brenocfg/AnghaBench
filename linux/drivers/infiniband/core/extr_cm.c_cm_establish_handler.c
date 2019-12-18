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
struct cm_work {int /*<<< orphan*/  list; int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct TYPE_6__ {TYPE_2__* port; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; int /*<<< orphan*/  msg; TYPE_3__ av; TYPE_1__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/  mad_agent; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_CM_ESTABLISHED ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 struct cm_id_private* cm_acquire_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  ib_cancel_mad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_establish_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	int ret;

	/* See comment in cm_establish about lookup. */
	cm_id_priv = cm_acquire_id(work->local_id, work->remote_id);
	if (!cm_id_priv)
		return -EINVAL;

	spin_lock_irq(&cm_id_priv->lock);
	if (cm_id_priv->id.state != IB_CM_ESTABLISHED) {
		spin_unlock_irq(&cm_id_priv->lock);
		goto out;
	}

	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
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