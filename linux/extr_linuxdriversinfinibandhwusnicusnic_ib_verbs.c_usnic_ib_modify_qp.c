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
struct usnic_ib_qp_grp {TYPE_2__* vf; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int port_num; int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pf; } ;
struct TYPE_3__ {int /*<<< orphan*/  usdev_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usnic_ib_qp_grp* to_uqp_grp (struct ib_qp*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 
 int /*<<< orphan*/  usnic_err (char*,int) ; 
 int usnic_ib_qp_grp_modify (struct usnic_ib_qp_grp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int usnic_ib_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
				int attr_mask, struct ib_udata *udata)
{
	struct usnic_ib_qp_grp *qp_grp;
	int status;
	usnic_dbg("\n");

	qp_grp = to_uqp_grp(ibqp);

	mutex_lock(&qp_grp->vf->pf->usdev_lock);
	if ((attr_mask & IB_QP_PORT) && attr->port_num != 1) {
		/* usnic devices only have one port */
		status = -EINVAL;
		goto out_unlock;
	}
	if (attr_mask & IB_QP_STATE) {
		status = usnic_ib_qp_grp_modify(qp_grp, attr->qp_state, NULL);
	} else {
		usnic_err("Unhandled request, attr_mask=0x%x\n", attr_mask);
		status = -EINVAL;
	}

out_unlock:
	mutex_unlock(&qp_grp->vf->pf->usdev_lock);
	return status;
}