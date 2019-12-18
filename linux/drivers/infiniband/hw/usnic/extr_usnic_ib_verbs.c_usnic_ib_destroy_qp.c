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
struct usnic_ib_vf {TYPE_1__* pf; } ;
struct usnic_ib_qp_grp {int /*<<< orphan*/  link; int /*<<< orphan*/  grp_id; struct usnic_ib_vf* vf; } ;
struct ib_udata {int dummy; } ;
struct ib_qp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  usdev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_RESET ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_grp_destroy (struct usnic_ib_qp_grp*) ; 
 struct usnic_ib_qp_grp* to_uqp_grp (struct ib_qp*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ usnic_ib_qp_grp_modify (struct usnic_ib_qp_grp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int usnic_ib_destroy_qp(struct ib_qp *qp, struct ib_udata *udata)
{
	struct usnic_ib_qp_grp *qp_grp;
	struct usnic_ib_vf *vf;

	usnic_dbg("\n");

	qp_grp = to_uqp_grp(qp);
	vf = qp_grp->vf;
	mutex_lock(&vf->pf->usdev_lock);
	if (usnic_ib_qp_grp_modify(qp_grp, IB_QPS_RESET, NULL)) {
		usnic_err("Failed to move qp grp %u to reset\n",
				qp_grp->grp_id);
	}

	list_del(&qp_grp->link);
	qp_grp_destroy(qp_grp);
	mutex_unlock(&vf->pf->usdev_lock);

	return 0;
}