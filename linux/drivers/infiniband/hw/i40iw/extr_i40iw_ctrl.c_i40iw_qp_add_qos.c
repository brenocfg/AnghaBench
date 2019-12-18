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
struct i40iw_sc_vsi {TYPE_1__* qos; } ;
struct i40iw_sc_qp {int on_qoslist; size_t user_pri; int /*<<< orphan*/  list; int /*<<< orphan*/  qs_handle; struct i40iw_sc_vsi* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  qplist; int /*<<< orphan*/  qs_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i40iw_qp_add_qos(struct i40iw_sc_qp *qp)
{
	struct i40iw_sc_vsi *vsi = qp->vsi;
	unsigned long flags;

	if (qp->on_qoslist)
		return;
	spin_lock_irqsave(&vsi->qos[qp->user_pri].lock, flags);
	qp->qs_handle = vsi->qos[qp->user_pri].qs_handle;
	list_add(&qp->list, &vsi->qos[qp->user_pri].qplist);
	qp->on_qoslist = true;
	spin_unlock_irqrestore(&vsi->qos[qp->user_pri].lock, flags);
}