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
struct qedr_device_attr {scalar_t__ max_sqe; scalar_t__ max_inline; scalar_t__ max_sge; } ;
struct qedr_dev {struct qedr_device_attr attr; } ;
struct ib_udata {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_send_wr; scalar_t__ max_inline_data; scalar_t__ max_send_sge; scalar_t__ max_recv_sge; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; TYPE_1__ cap; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,scalar_t__,...) ; 
 int EINVAL ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_RC ; 
 int /*<<< orphan*/  QEDR_MSG_QP ; 

__attribute__((used)) static int qedr_check_qp_attrs(struct ib_pd *ibpd, struct qedr_dev *dev,
			       struct ib_qp_init_attr *attrs,
			       struct ib_udata *udata)
{
	struct qedr_device_attr *qattr = &dev->attr;

	/* QP0... attrs->qp_type == IB_QPT_GSI */
	if (attrs->qp_type != IB_QPT_RC && attrs->qp_type != IB_QPT_GSI) {
		DP_DEBUG(dev, QEDR_MSG_QP,
			 "create qp: unsupported qp type=0x%x requested\n",
			 attrs->qp_type);
		return -EINVAL;
	}

	if (attrs->cap.max_send_wr > qattr->max_sqe) {
		DP_ERR(dev,
		       "create qp: cannot create a SQ with %d elements (max_send_wr=0x%x)\n",
		       attrs->cap.max_send_wr, qattr->max_sqe);
		return -EINVAL;
	}

	if (attrs->cap.max_inline_data > qattr->max_inline) {
		DP_ERR(dev,
		       "create qp: unsupported inline data size=0x%x requested (max_inline=0x%x)\n",
		       attrs->cap.max_inline_data, qattr->max_inline);
		return -EINVAL;
	}

	if (attrs->cap.max_send_sge > qattr->max_sge) {
		DP_ERR(dev,
		       "create qp: unsupported send_sge=0x%x requested (max_send_sge=0x%x)\n",
		       attrs->cap.max_send_sge, qattr->max_sge);
		return -EINVAL;
	}

	if (attrs->cap.max_recv_sge > qattr->max_sge) {
		DP_ERR(dev,
		       "create qp: unsupported recv_sge=0x%x requested (max_recv_sge=0x%x)\n",
		       attrs->cap.max_recv_sge, qattr->max_sge);
		return -EINVAL;
	}

	/* Unprivileged user space cannot create special QP */
	if (udata && attrs->qp_type == IB_QPT_GSI) {
		DP_ERR(dev,
		       "create qp: userspace can't create special QPs of type=0x%x\n",
		       attrs->qp_type);
		return -EINVAL;
	}

	return 0;
}