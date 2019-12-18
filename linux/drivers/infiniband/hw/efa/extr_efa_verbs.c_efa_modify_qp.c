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
struct ib_udata {scalar_t__ inlen; } ;
struct ib_qp_attr {int cur_qp_state; int qp_state; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  en_sqd_async_notify; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct efa_qp {int state; int /*<<< orphan*/  qp_handle; } ;
struct efa_dev {int /*<<< orphan*/  edev; int /*<<< orphan*/  ibdev; } ;
struct efa_com_modify_qp_params {int modify_mask; int cur_qp_state; int qp_state; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  sq_drained_async_notify; int /*<<< orphan*/  qp_handle; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFA_ADMIN_CUR_QP_STATE_BIT ; 
 int /*<<< orphan*/  EFA_ADMIN_QKEY_BIT ; 
 int /*<<< orphan*/  EFA_ADMIN_QP_STATE_BIT ; 
 int /*<<< orphan*/  EFA_ADMIN_SQ_DRAINED_ASYNC_NOTIFY_BIT ; 
 int /*<<< orphan*/  EFA_ADMIN_SQ_PSN_BIT ; 
 int EINVAL ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_EN_SQD_ASYNC_NOTIFY ; 
 int IB_QP_QKEY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int efa_com_modify_qp (int /*<<< orphan*/ *,struct efa_com_modify_qp_params*) ; 
 int efa_modify_qp_validate (struct efa_dev*,struct efa_qp*,struct ib_qp_attr*,int,int,int) ; 
 int /*<<< orphan*/  ib_is_udata_cleared (struct ib_udata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 
 struct efa_qp* to_eqp (struct ib_qp*) ; 

int efa_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *qp_attr,
		  int qp_attr_mask, struct ib_udata *udata)
{
	struct efa_dev *dev = to_edev(ibqp->device);
	struct efa_com_modify_qp_params params = {};
	struct efa_qp *qp = to_eqp(ibqp);
	enum ib_qp_state cur_state;
	enum ib_qp_state new_state;
	int err;

	if (udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		return -EINVAL;
	}

	cur_state = qp_attr_mask & IB_QP_CUR_STATE ? qp_attr->cur_qp_state :
						     qp->state;
	new_state = qp_attr_mask & IB_QP_STATE ? qp_attr->qp_state : cur_state;

	err = efa_modify_qp_validate(dev, qp, qp_attr, qp_attr_mask, cur_state,
				     new_state);
	if (err)
		return err;

	params.qp_handle = qp->qp_handle;

	if (qp_attr_mask & IB_QP_STATE) {
		params.modify_mask |= BIT(EFA_ADMIN_QP_STATE_BIT) |
				      BIT(EFA_ADMIN_CUR_QP_STATE_BIT);
		params.cur_qp_state = qp_attr->cur_qp_state;
		params.qp_state = qp_attr->qp_state;
	}

	if (qp_attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY) {
		params.modify_mask |=
			BIT(EFA_ADMIN_SQ_DRAINED_ASYNC_NOTIFY_BIT);
		params.sq_drained_async_notify = qp_attr->en_sqd_async_notify;
	}

	if (qp_attr_mask & IB_QP_QKEY) {
		params.modify_mask |= BIT(EFA_ADMIN_QKEY_BIT);
		params.qkey = qp_attr->qkey;
	}

	if (qp_attr_mask & IB_QP_SQ_PSN) {
		params.modify_mask |= BIT(EFA_ADMIN_SQ_PSN_BIT);
		params.sq_psn = qp_attr->sq_psn;
	}

	err = efa_com_modify_qp(&dev->edev, &params);
	if (err)
		return err;

	qp->state = new_state;

	return 0;
}