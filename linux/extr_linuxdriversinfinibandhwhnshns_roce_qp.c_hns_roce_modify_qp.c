#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int cur_qp_state; int qp_state; scalar_t__ port_num; scalar_t__ pkey_index; scalar_t__ path_mtu; scalar_t__ max_rd_atomic; scalar_t__ max_dest_rd_atomic; } ;
struct ib_qp {int /*<<< orphan*/  qp_type; scalar_t__ uobject; int /*<<< orphan*/  device; } ;
struct TYPE_12__ {scalar_t__ virt_addr; } ;
struct TYPE_11__ {int head; } ;
struct TYPE_10__ {scalar_t__ virt_addr; } ;
struct TYPE_9__ {int head; } ;
struct hns_roce_qp {int sdb_en; int port; int /*<<< orphan*/  mutex; TYPE_4__ rdb; TYPE_3__ rq; TYPE_2__ sdb; TYPE_1__ sq; scalar_t__ state; } ;
struct TYPE_15__ {scalar_t__ num_ports; scalar_t__* pkey_table_len; scalar_t__ max_mtu; scalar_t__ max_qp_init_rdma; scalar_t__ max_qp_dest_rdma; scalar_t__ min_wqes; } ;
struct TYPE_14__ {TYPE_5__** netdevs; } ;
struct hns_roce_dev {TYPE_8__* hw; TYPE_7__ caps; TYPE_6__ iboe; struct device* dev; } ;
struct device {int dummy; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;
struct TYPE_16__ {int (* modify_qp ) (struct ib_qp*,struct ib_qp_attr*,int,int,int) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  IB_LINK_LAYER_ETHERNET ; 
 scalar_t__ IB_MTU_2048 ; 
 scalar_t__ IB_MTU_256 ; 
 scalar_t__ IB_MTU_4096 ; 
 int IB_QPS_ERR ; 
 int IB_QPS_RESET ; 
 int IB_QP_CUR_STATE ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  ib_modify_qp_is_ok (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int iboe_get_mtu (int /*<<< orphan*/ ) ; 
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
	struct device *dev = hr_dev->dev;
	int ret = -EINVAL;
	int p;
	enum ib_mtu active_mtu;

	mutex_lock(&hr_qp->mutex);

	cur_state = attr_mask & IB_QP_CUR_STATE ?
		    attr->cur_qp_state : (enum ib_qp_state)hr_qp->state;
	new_state = attr_mask & IB_QP_STATE ?
		    attr->qp_state : cur_state;

	if (ibqp->uobject &&
	    (attr_mask & IB_QP_STATE) && new_state == IB_QPS_ERR) {
		if (hr_qp->sdb_en == 1) {
			hr_qp->sq.head = *(int *)(hr_qp->sdb.virt_addr);
			hr_qp->rq.head = *(int *)(hr_qp->rdb.virt_addr);
		} else {
			dev_warn(dev, "flush cqe is not supported in userspace!\n");
			goto out;
		}
	}

	if (!ib_modify_qp_is_ok(cur_state, new_state, ibqp->qp_type, attr_mask,
				IB_LINK_LAYER_ETHERNET)) {
		dev_err(dev, "ib_modify_qp_is_ok failed\n");
		goto out;
	}

	if ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 || attr->port_num > hr_dev->caps.num_ports)) {
		dev_err(dev, "attr port_num invalid.attr->port_num=%d\n",
			attr->port_num);
		goto out;
	}

	if (attr_mask & IB_QP_PKEY_INDEX) {
		p = attr_mask & IB_QP_PORT ? (attr->port_num - 1) : hr_qp->port;
		if (attr->pkey_index >= hr_dev->caps.pkey_table_len[p]) {
			dev_err(dev, "attr pkey_index invalid.attr->pkey_index=%d\n",
				attr->pkey_index);
			goto out;
		}
	}

	if (attr_mask & IB_QP_PATH_MTU) {
		p = attr_mask & IB_QP_PORT ? (attr->port_num - 1) : hr_qp->port;
		active_mtu = iboe_get_mtu(hr_dev->iboe.netdevs[p]->mtu);

		if ((hr_dev->caps.max_mtu == IB_MTU_4096 &&
		    attr->path_mtu > IB_MTU_4096) ||
		    (hr_dev->caps.max_mtu == IB_MTU_2048 &&
		    attr->path_mtu > IB_MTU_2048) ||
		    attr->path_mtu < IB_MTU_256 ||
		    attr->path_mtu > active_mtu) {
			dev_err(dev, "attr path_mtu(%d)invalid while modify qp",
				attr->path_mtu);
			goto out;
		}
	}

	if (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic > hr_dev->caps.max_qp_init_rdma) {
		dev_err(dev, "attr max_rd_atomic invalid.attr->max_rd_atomic=%d\n",
			attr->max_rd_atomic);
		goto out;
	}

	if (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic > hr_dev->caps.max_qp_dest_rdma) {
		dev_err(dev, "attr max_dest_rd_atomic invalid.attr->max_dest_rd_atomic=%d\n",
			attr->max_dest_rd_atomic);
		goto out;
	}

	if (cur_state == new_state && cur_state == IB_QPS_RESET) {
		if (hr_dev->caps.min_wqes) {
			ret = -EPERM;
			dev_err(dev, "cur_state=%d new_state=%d\n", cur_state,
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