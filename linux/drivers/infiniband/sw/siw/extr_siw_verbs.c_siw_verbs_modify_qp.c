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
struct siw_qp_attrs {scalar_t__ state; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int tx_suspend; } ;
struct siw_qp {int /*<<< orphan*/  state_lock; TYPE_1__ tx_ctx; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int qp_access_flags; size_t qp_state; } ;
struct ib_qp {int dummy; } ;
typedef  int /*<<< orphan*/  new_attrs ;
typedef  enum siw_qp_attr_mask { ____Placeholder_siw_qp_attr_mask } siw_qp_attr_mask ;

/* Variables and functions */
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_STATE ; 
 int SIW_QP_ATTR_ACCESS_FLAGS ; 
 int SIW_QP_ATTR_STATE ; 
 scalar_t__ SIW_QP_STATE_RTS ; 
 int /*<<< orphan*/  SIW_RDMA_BIND_ENABLED ; 
 int /*<<< orphan*/  SIW_RDMA_READ_ENABLED ; 
 int /*<<< orphan*/  SIW_RDMA_WRITE_ENABLED ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__* ib_qp_state_to_siw_qp_state ; 
 int /*<<< orphan*/ * ib_qp_state_to_string ; 
 int /*<<< orphan*/  memset (struct siw_qp_attrs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,int /*<<< orphan*/ ) ; 
 int siw_qp_modify (struct siw_qp*,struct siw_qp_attrs*,int) ; 
 struct siw_qp* to_siw_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int siw_verbs_modify_qp(struct ib_qp *base_qp, struct ib_qp_attr *attr,
			int attr_mask, struct ib_udata *udata)
{
	struct siw_qp_attrs new_attrs;
	enum siw_qp_attr_mask siw_attr_mask = 0;
	struct siw_qp *qp = to_siw_qp(base_qp);
	int rv = 0;

	if (!attr_mask)
		return 0;

	memset(&new_attrs, 0, sizeof(new_attrs));

	if (attr_mask & IB_QP_ACCESS_FLAGS) {
		siw_attr_mask = SIW_QP_ATTR_ACCESS_FLAGS;

		if (attr->qp_access_flags & IB_ACCESS_REMOTE_READ)
			new_attrs.flags |= SIW_RDMA_READ_ENABLED;
		if (attr->qp_access_flags & IB_ACCESS_REMOTE_WRITE)
			new_attrs.flags |= SIW_RDMA_WRITE_ENABLED;
		if (attr->qp_access_flags & IB_ACCESS_MW_BIND)
			new_attrs.flags |= SIW_RDMA_BIND_ENABLED;
	}
	if (attr_mask & IB_QP_STATE) {
		siw_dbg_qp(qp, "desired IB QP state: %s\n",
			   ib_qp_state_to_string[attr->qp_state]);

		new_attrs.state = ib_qp_state_to_siw_qp_state[attr->qp_state];

		if (new_attrs.state > SIW_QP_STATE_RTS)
			qp->tx_ctx.tx_suspend = 1;

		siw_attr_mask |= SIW_QP_ATTR_STATE;
	}
	if (!siw_attr_mask)
		goto out;

	down_write(&qp->state_lock);

	rv = siw_qp_modify(qp, &new_attrs, siw_attr_mask);

	up_write(&qp->state_lock);
out:
	return rv;
}