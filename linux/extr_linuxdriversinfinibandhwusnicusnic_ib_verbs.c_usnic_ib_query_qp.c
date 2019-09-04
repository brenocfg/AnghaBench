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
struct usnic_ib_vf {TYPE_2__* pf; } ;
struct TYPE_3__ {int qp_type; } ;
struct usnic_ib_qp_grp {TYPE_1__ ibqp; int /*<<< orphan*/  state; struct usnic_ib_vf* vf; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  qkey; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ib_qp_attr {int /*<<< orphan*/  qkey; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  usdev_lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_UD 128 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usnic_ib_qp_grp* to_uqp_grp (struct ib_qp*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 
 int /*<<< orphan*/  usnic_err (char*,int) ; 

int usnic_ib_query_qp(struct ib_qp *qp, struct ib_qp_attr *qp_attr,
				int qp_attr_mask,
				struct ib_qp_init_attr *qp_init_attr)
{
	struct usnic_ib_qp_grp *qp_grp;
	struct usnic_ib_vf *vf;
	int err;

	usnic_dbg("\n");

	memset(qp_attr, 0, sizeof(*qp_attr));
	memset(qp_init_attr, 0, sizeof(*qp_init_attr));

	qp_grp = to_uqp_grp(qp);
	vf = qp_grp->vf;
	mutex_lock(&vf->pf->usdev_lock);
	usnic_dbg("\n");
	qp_attr->qp_state = qp_grp->state;
	qp_attr->cur_qp_state = qp_grp->state;

	switch (qp_grp->ibqp.qp_type) {
	case IB_QPT_UD:
		qp_attr->qkey = 0;
		break;
	default:
		usnic_err("Unexpected qp_type %d\n", qp_grp->ibqp.qp_type);
		err = -EINVAL;
		goto err_out;
	}

	mutex_unlock(&vf->pf->usdev_lock);
	return 0;

err_out:
	mutex_unlock(&vf->pf->usdev_lock);
	return err;
}