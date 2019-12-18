#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int cur_qp_state; int qp_state; } ;
struct ib_qp {int /*<<< orphan*/  qp_type; scalar_t__ uobject; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {scalar_t__ virt_addr; } ;
struct TYPE_9__ {int head; } ;
struct TYPE_8__ {scalar_t__ virt_addr; } ;
struct TYPE_7__ {int head; } ;
struct hns_roce_qp {int sdb_en; int rdb_en; int /*<<< orphan*/  mutex; TYPE_4__ rdb; TYPE_3__ rq; TYPE_2__ sdb; TYPE_1__ sq; scalar_t__ state; } ;
struct TYPE_11__ {scalar_t__ min_wqes; } ;
struct hns_roce_dev {TYPE_6__* hw; int /*<<< orphan*/  ib_dev; TYPE_5__ caps; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
struct TYPE_12__ {int (* modify_qp ) (struct ib_qp*,struct ib_qp_attr*,int,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int IB_QPS_ERR ; 
 int IB_QPS_RESET ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_STATE ; 
 int hns_roce_check_qp_attr (struct ib_qp*,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  ib_modify_qp_is_ok (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ibdev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_qp*,struct ib_qp_attr*,int,int,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

int hns_roce_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
		       int attr_mask, struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	enum ib_qp_state cur_state, new_state;
	int ret = -EINVAL;

	mutex_lock(&hr_qp->mutex);

	cur_state = attr_mask & IB_QP_CUR_STATE ?
		    attr->cur_qp_state : (enum ib_qp_state)hr_qp->state;
	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;

	if (ibqp->uobject &&
	    (attr_mask & IB_QP_STATE) && new_state == IB_QPS_ERR) {
		if (hr_qp->sdb_en == 1) {
			hr_qp->sq.head = *(int *)(hr_qp->sdb.virt_addr);

			if (hr_qp->rdb_en == 1)
				hr_qp->rq.head = *(int *)(hr_qp->rdb.virt_addr);
		} else {
			ibdev_warn(&hr_dev->ib_dev,
				  "flush cqe is not supported in userspace!\n");
			goto out;
		}
	}

	if (!ib_modify_qp_is_ok(cur_state, new_state, ibqp->qp_type,
				attr_mask)) {
		ibdev_err(&hr_dev->ib_dev, "ib_modify_qp_is_ok failed\n");
		goto out;
	}

	ret = hns_roce_check_qp_attr(ibqp, attr, attr_mask);
	if (ret)
		goto out;

	if (cur_state == new_state && cur_state == IB_QPS_RESET) {
		if (hr_dev->caps.min_wqes) {
			ret = -EPERM;
			ibdev_err(&hr_dev->ib_dev,
				"cur_state=%d new_state=%d\n", cur_state,
				new_state);
		} else {
			ret = 0;
		}

		goto out;
	}

	ret = hr_dev->hw->modify_qp(ibqp, attr, attr_mask, cur_state,
				    new_state);

out:
	mutex_unlock(&hr_qp->mutex);

	return ret;
}