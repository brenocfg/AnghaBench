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
struct ib_qp_attr {scalar_t__ port_num; scalar_t__ pkey_index; scalar_t__ max_rd_atomic; scalar_t__ max_dest_rd_atomic; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct hns_roce_qp {int port; } ;
struct TYPE_2__ {scalar_t__ num_ports; scalar_t__* pkey_table_len; scalar_t__ max_qp_init_rdma; scalar_t__ max_qp_dest_rdma; } ;
struct hns_roce_dev {int /*<<< orphan*/  ib_dev; TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int check_mtu_validate (struct hns_roce_dev*,struct hns_roce_qp*,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int hns_roce_check_qp_attr(struct ib_qp *ibqp, struct ib_qp_attr *attr,
				  int attr_mask)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	int p;

	if ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 || attr->port_num > hr_dev->caps.num_ports)) {
		ibdev_err(&hr_dev->ib_dev,
			"attr port_num invalid.attr->port_num=%d\n",
			attr->port_num);
		return -EINVAL;
	}

	if (attr_mask & IB_QP_PKEY_INDEX) {
		p = attr_mask & IB_QP_PORT ? (attr->port_num - 1) : hr_qp->port;
		if (attr->pkey_index >= hr_dev->caps.pkey_table_len[p]) {
			ibdev_err(&hr_dev->ib_dev,
				"attr pkey_index invalid.attr->pkey_index=%d\n",
				attr->pkey_index);
			return -EINVAL;
		}
	}

	if (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic > hr_dev->caps.max_qp_init_rdma) {
		ibdev_err(&hr_dev->ib_dev,
			"attr max_rd_atomic invalid.attr->max_rd_atomic=%d\n",
			attr->max_rd_atomic);
		return -EINVAL;
	}

	if (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic > hr_dev->caps.max_qp_dest_rdma) {
		ibdev_err(&hr_dev->ib_dev,
			"attr max_dest_rd_atomic invalid.attr->max_dest_rd_atomic=%d\n",
			attr->max_dest_rd_atomic);
		return -EINVAL;
	}

	if (attr_mask & IB_QP_PATH_MTU)
		return check_mtu_validate(hr_dev, hr_qp, attr, attr_mask);

	return 0;
}